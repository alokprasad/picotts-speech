#include<speech.hpp>
main()
{
	Speech obj;
	char *text = "The mission team has several theories for why they haven't been able to contact the pair. WALL-E has a leaky thruster.";
	obj.setLanguage("en-US");
	obj.setSpeed(105);
	obj.setPitch(110);
	obj.renderSpeech(text);

	system("aplay /tmp/speech.wav");
	return 0;
}
