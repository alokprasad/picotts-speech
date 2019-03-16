/*original Credit to below*/
package com.doepiccoding.voiceanalizer;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Handler;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.Timer;

public class MainActivity extends Activity {

	private static final int sampleRate = 8000;
	private AudioRecord audio;
	private int bufferSize;
	private double lastLevel = 0;
	private double cLastLevel = 0;
	private Thread thread;
	private static final int SAMPLE_DELAY = 50;
	private static final int VOICE_THRESHOLD = 5;
    private static final int SILENCE_THRESHOLD = 100;
	private static  int recordingFlag = 0;
	private ImageView mouthImage;
	private TextView levelText;


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		levelText = (TextView) findViewById(R.id.textView2);

		mouthImage = (ImageView)findViewById(R.id.mounthHolder);
		mouthImage.setKeepScreenOn(true);
		levelText.setText("RECORDING STOPPED");
		try {
			bufferSize = AudioRecord
					.getMinBufferSize(sampleRate, AudioFormat.CHANNEL_IN_MONO,
							AudioFormat.ENCODING_PCM_16BIT);
		} catch (Exception e) {
			android.util.Log.e("TrackingFlow", "Exception", e);
		}
	}

	protected void onResume() {
		super.onResume();
		audio = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate,
				AudioFormat.CHANNEL_IN_MONO,
				AudioFormat.ENCODING_PCM_16BIT, bufferSize);

		audio.startRecording();
		thread = new Thread(new Runnable() {
			public void run() {
				while(thread != null && !thread.isInterrupted()){
					//Let's make the thread sleep for a the approximate sampling time
					try{Thread.sleep(SAMPLE_DELAY);}catch(InterruptedException ie){ie.printStackTrace();}
					readAudioBuffer();//After this call we can get the last value assigned to the lastLevel variable
					
					runOnUiThread(new Runnable() {
						
						@Override
						public void run() {

							//levelText.setText(String.valueOf((int)lastLevel/10));

							if (lastLevel/10 > VOICE_THRESHOLD) {


                                if (recordingFlag == 0) {
                                    levelText.setText("RECORDING STARTED...");
                                    recordingFlag = 1;
                                    cLastLevel = 0;
                                }

                                /*{Start Actual Recording Here}*/

                                new Handler().postDelayed(new Runnable() {
                                    @Override
                                    public void run() {

										/* ALOK:Check here cumulative level for 2 seconds it is less than some silence
										threshold stop the recording.
										 */


                                            //levelText.setText("RECORDING STOPPED");
										    recordingFlag = 0;
                                            levelText.setText("RECORDING STOPPED" + String.valueOf(cLastLevel));
											cLastLevel = 0;

                                    }
                                }, 2000); /*wait for 2 seconds if silence */

                            }


							if(lastLevel > 0 && lastLevel <= 50){
								mouthImage.setImageResource(R.drawable.mouth4);
							}else
							if(lastLevel > 50 && lastLevel <= 100){
								mouthImage.setImageResource(R.drawable.mouth3);

							}else
							if(lastLevel > 100 && lastLevel <= 170){
								mouthImage.setImageResource(R.drawable.mouth2);
							}
							if(lastLevel > 170){
								mouthImage.setImageResource(R.drawable.mouth1);
							}
						}
					});
				}
			}
		});
		thread.start();
	}

	/**
	 * Functionality that gets the sound level out of the sample
	 */
	private void readAudioBuffer() {

		try {
			short[] buffer = new short[bufferSize];

			int bufferReadResult = 1;

			if (audio != null) {

				// Sense the voice...
				bufferReadResult = audio.read(buffer, 0, bufferSize);
				double sumLevel = 0;
				for (int i = 0; i < bufferReadResult; i++) {
					sumLevel += buffer[i];
				}
				lastLevel = Math.abs((sumLevel / bufferReadResult));
				cLastLevel = lastLevel + cLastLevel;
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void onPause() {
		super.onPause();
		thread.interrupt();
		thread = null;
		try {
			if (audio != null) {
				audio.stop();
				audio.release();
				audio = null;
			}
		} catch (Exception e) {e.printStackTrace();}
	}
}
