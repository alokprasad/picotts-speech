#./testpico "<pitch level='95'><speed level='105'>How are you? </speed></pitch> " | aplay --rate=16000 --channels=1 --format=S16_LE
#./testpico  "<pitch level='105'><speed level='105'> Mission team members repurposed the rover's navigation </speed></pitch>" | aplay --rate=16000 --channels=1 --format=S16_LE
./testpico  "<pitch level='105'><speed level='100'> How are you? </speed></pitch>" -f | aplay --rate=16000 --channels=1 --format=S16_LE
#./testpico "<pitch level='90'><speed level='105'>This is a test of the Pico TTS engine on the android</speed></pitch> " | aplay --rate=16000 --channels=1 --format=S16_LE
