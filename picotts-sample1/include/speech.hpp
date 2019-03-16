/*
 * Copyright (C) 2014 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#include <string>
#include <vector>


#include <picoapi.h>
#include <picoapid.h>
#include <picoos.h>

/*
namespace yarp{
    namespace dev{
        class Speech;
    }
}
*/


/****************************************************************
 * @brief The yarp::dev::Speech class
 */
class Speech { 

public:

    	Speech();
    ~Speech();

    /*
	Speech() {
		language = "en-US";
		supportedLangs.push_back("en-US");
		supportedLangs.push_back("en-GB");
		supportedLangs.push_back("es-ES");
		supportedLangs.push_back("fr-FR");
		supportedLangs.push_back("it-IT");
		supportedLangs.push_back("de-DE");
		// picotts
		picoMemArea         = NULL;
		picoSystem          = NULL;
		picoTaResource      = NULL;
		picoSgResource      = NULL;
		picoUtppResource    = NULL;
		picoEngine          = NULL;
		picoTaFileName      = NULL;
		picoSgFileName      = NULL;
		picoUtppFileName    = NULL;
		picoTaResourceName  = NULL;
		picoSgResourceName  = NULL;
		picoUtppResourceName = NULL;
		picoSynthAbort = 0;
	}

	~Speech() {
		;
	}
*/

    // Speech_IDL
    virtual bool setLanguage(const std::string& language);
    virtual std::vector<std::string>  getSupportedLang();
    //virtual bool say(const std::string& text);
    virtual const std::string renderSpeech(const std::string &text) ;

    virtual bool setSpeed(const int16_t speed);
    virtual bool setPitch(const int16_t pitch);
    virtual int16_t getSpeed();
    virtual int16_t getPitch();

private:
    /**
     * @brief renderSpeech
     * @param text
     * @return the rendered wave file path
     */
    void releasePico();
private:
    std::string language;
    std::string pcmDevice;
    int pitch, speed;
    std::vector<std::string> supportedLangs;

private: // picotts
    /* adapation layer global variables */
    void *          picoMemArea;
    pico_System     picoSystem;
    pico_Resource   picoTaResource;
    pico_Resource   picoSgResource;
    pico_Resource   picoUtppResource;
    pico_Engine     picoEngine;
    pico_Char *     picoTaFileName;
    pico_Char *     picoSgFileName;
    pico_Char *     picoUtppFileName;
    pico_Char *     picoTaResourceName;
    pico_Char *     picoSgResourceName;
    pico_Char *     picoUtppResourceName;
    int picoSynthAbort;
};
