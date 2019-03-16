#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "../include/TtsEngine.h"

#define OUTPUT_BUFFER_SIZE (128 * 1024)

using namespace android;

static bool synthesis_complete = false;

static FILE *outfp = stdout;

#define DEFAULT_TTS_RATE        16000
#define DEFAULT_TTS_BUFFERSIZE  2048

// EQ + BOOST parameters
#define FILTER_LOWSHELF_ATTENUATION -18.0f // in dB
#define FILTER_TRANSITION_FREQ 1100.0f     // in Hz
#define FILTER_SHELF_SLOPE 1.0f            // Q
#define FILTER_GAIN 5.5f // linear gain


// ----------------------------------------------------------------------------
// EQ data
static double m_fa, m_fb, m_fc, m_fd, m_fe;
static double x0;  // x[n]
static double x1;  // x[n-1]
static double x2;  // x[n-2]
static double out0;// y[n]
static double out1;// y[n-1]
static double out2;// y[n-2]

static float fFilterLowshelfAttenuation = FILTER_LOWSHELF_ATTENUATION;
static float fFilterTransitionFreq = FILTER_TRANSITION_FREQ;
static float fFilterShelfSlope = FILTER_SHELF_SLOPE;
static float fFilterGain = FILTER_GAIN;
static bool  bUseFilter = false;

/* Speech Enhacement */
void initializeEQ() {
    double amp = float(pow(10.0, fFilterLowshelfAttenuation / 40.0));
    double w = 2.0 * M_PI * (fFilterTransitionFreq / DEFAULT_TTS_RATE);
    double sinw = float(sin(w));
    double cosw = float(cos(w));
    double beta = float(sqrt(amp)/fFilterShelfSlope);

    // initialize low-shelf parameters
    double b0 = amp * ((amp+1.0F) - ((amp-1.0F)*cosw) + (beta*sinw));
    double b1 = 2.0F * amp * ((amp-1.0F) - ((amp+1.0F)*cosw));
    double b2 = amp * ((amp+1.0F) - ((amp-1.0F)*cosw) - (beta*sinw));
    double a0 = (amp+1.0F) + ((amp-1.0F)*cosw) + (beta*sinw);
    double a1 = 2.0F * ((amp-1.0F) + ((amp+1.0F)*cosw));
    double a2 = -((amp+1.0F) + ((amp-1.0F)*cosw) - (beta*sinw));

    m_fa = fFilterGain * b0/a0;
    m_fb = fFilterGain * b1/a0;
    m_fc = fFilterGain * b2/a0;
    m_fd = a1/a0;
    m_fe = a2/a0;
}

void initializeFilter() {
    x0 = 0.0f;
    x1 = 0.0f;
    x2 = 0.0f;
    out0 = 0.0f;
    out1 = 0.0f;
    out2 = 0.0f;
}

void applyFilter(int16_t* buffer, size_t sampleCount) {

    for (size_t i=0 ; i<sampleCount ; i++) {

        x0 = (double) buffer[i];

        out0 = (m_fa*x0) + (m_fb*x1) + (m_fc*x2) + (m_fd*out1) + (m_fe*out2);

        x2 = x1;
        x1 = x0;

        out2 = out1;
        out1 = out0;

        if (out0 > 32767.0f) {
            buffer[i] = 32767;
        } else if (out0 < -32768.0f) {
            buffer[i] = -32768;
        } else {
            buffer[i] = (int16_t) out0;
        }
    }
}


// @param [inout] void *&       - The userdata pointer set in the original
//                                 synth call
// @param [in]    uint32_t      - Track sampling rate in Hz
// @param [in] tts_audio_format - The audio format
// @param [in]    int           - The number of channels
// @param [inout] int8_t *&     - A buffer of audio data only valid during the
//                                execution of the callback
// @param [inout] size_t  &     - The size of the buffer
// @param [in] tts_synth_status - indicate whether the synthesis is done, or
//                                 if more data is to be synthesized.
// @return TTS_CALLBACK_HALT to indicate the synthesis must stop,
//         TTS_CALLBACK_CONTINUE to indicate the synthesis must continue if
//            there is more data to produce.

tts_callback_status synth_done(void *& userdata, uint32_t sample_rate,
        tts_audio_format audio_format, int channels, int8_t *& data, size_t& size, tts_synth_status status)
{
	//fprintf(stderr, "TTS callback, rate: %d, data size: %d, status: %i\n", sample_rate, size, status);

	
	if (status == TTS_SYNTH_DONE)
	{
		synthesis_complete = true;
	}

	if ((size == OUTPUT_BUFFER_SIZE) || (status == TTS_SYNTH_DONE))
	{
		if(bUseFilter)
			applyFilter((int16_t*)data,size/2);
		
		fwrite(data, size, 1, outfp);
	}

	return TTS_CALLBACK_CONTINUE;
}

static void usage(void)
{
	fprintf(stderr, "\nUsage:\n\n" \
					"testpico [-o raw_filename(not wave)] \"Text to speak\"\n\n" \
		   			"  -o\tFile to write audio to (default stdout)"\
					"e.g usage: /testpico \"This is a test of the Pico TTS engine on the android \" | aplay --rate=16000 --channels=1 --format=S16_LE \n");
	exit(0);
}

int main(int argc, char *argv[])
{
	tts_result result;
	TtsEngine* ttsEngine = getTtsEngine();
	int8_t* synthBuffer;
	char* synthInput = NULL;
	int currentOption;
	char* outputFilename = NULL;

	fprintf(stderr, "Pico TTS Test App\n");

	if (argc == 1)
	{
		usage();
	}

	while ( (currentOption = getopt(argc, argv, "o:h:f")) != -1)
	{
		switch (currentOption)
		{
			case 'o':
				outputFilename = optarg;
				fprintf(stderr, "Output audio to file '%s'\n", outputFilename);
				break;
			case 'h':
				usage();
				break;
			case 'f':
				bUseFilter = true;
				break;
			default:
				printf ("Getopt returned character code 0%o ??\n", currentOption);
		}
	}

    if (optind < argc)
    {
    	synthInput = argv[optind];
    }

    if (!synthInput)
    {
    	fprintf(stderr, "Error: no input string\n");
    	usage();
    }

    fprintf(stderr, "Input string: \"%s\"\n", synthInput);

	synthBuffer = new int8_t[OUTPUT_BUFFER_SIZE];

	result = ttsEngine->init(synth_done, "/system/tts/lang_pico/");

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to init TTS\n");
	}

	// Force English for now
	result = ttsEngine->setLanguage("eng", "GBR", "");

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to load language\n");
	}

	if (outputFilename)
	{
		outfp = fopen(outputFilename, "wb");
	}

	fprintf(stderr, "Synthesising text...\n");

	//Filter 
	initializeFilter();
        initializeEQ();


	result = ttsEngine->synthesizeText(synthInput, synthBuffer, OUTPUT_BUFFER_SIZE, (void *)NULL);

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to synth text\n");
	}

	while(!synthesis_complete)
	{
		usleep(100);
	}

	fprintf(stderr, "Completed.\n");

	if (outputFilename)
	{
		fclose(outfp);
	}

	result = ttsEngine->shutdown();

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to shutdown TTS\n");
	}

	delete [] synthBuffer;

	return 0;
}
