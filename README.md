**Checkout tts_pico repo**

git clone https://git.visteon.com/SmartVoiceAssistant/sns_experiments/tts_pico.git```

**build pico tts library**

First build libttspico.so which is linked to pico2wave app.
 ```
 cd picotts-src
 bash build-pico.sh android --> copy libsvoxpico.so to /data/local
 bash build-pico.sh linux ---> copy libsvoxpico.so to /usr/lib/i386-linux-gnu/libsvoxpico.so
```

**build pico2wave app**
```
cd pico2wave
bash build.sh android --> copy pico2wave to /data/local
bash build.sh linux 
```
**Run the app**
```
msm8996:/data/local # ./pico2wave
pico2wave started,wavefile:/data/local/tts.wav
picotts initialized(0)
Wavefile successfully Created
```