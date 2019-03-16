1. First compile pico tts

```
cd  picotts-src
bash build-pico.sh linux --> Creates libsvoxpico.so

cp libsvoxpico.so to /usr/lib/i386-linux-gnu/libsvoxpico.so
```

2. Compile libttscompat.so (TTS interface )

```
make from top level directory - > creates libttscompat.so
```

3. compile test app.

```
cd test
make --> creates testpico
```

4. Run Test app

```
./testpico "This is a test of the Pico TTS engine on the android " | aplay --rate=16000 --channels=1 --format=S16_LE

on Android 

./testpico "This is a test of the Pico TTS engine on the android " &> sample.raw 
( paly this sample on linux with aplay)
```