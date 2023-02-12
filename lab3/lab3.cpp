#include <iostream>
#include <fstream>
#include "wav_reader.h"
#include "sound_header.h"
#include <math.h>
#include <algorithm>
#include "sound_processor.h"

using namespace std;

int main(int argc, char** argv)
{
	/*sound_header sh;

	wav_writer test;
	test.open("test.wav", ios::binary);
	sh.freq = 44100;
	sh.bytes_per_sec = 88200;
	sh.channels = 1;
	sh.primary_file_len = 1000042;
	sh.file_len = 1000000;
	test << sh;
	for (int i = 0; i < 1000000; ++i) {
		short temp = (sin((float)i * 0.03f) * (sin((float)i * 0.03f) * (i / 10)));
		test << temp;
	}

	wav_reader audio;
	audio.open("test.wav");
	audio >> sh;
	cout << string(sh);*/

	/*for (int i = 1; i <= 5; ++i) {
		sound_header sh;
		wav_reader audio;
		audio.open("music/Alarm0" + to_string(i) + ".wav");
		audio >> sh;
		cout << string(sh) << endl;
	}*/

	//string requset = "sound_processor music/Alarm01.wav music/Alarm02.wav music/Alarm03.wav -c config.txt -o music/output.wav";
	sound_processor processor(argc, argv);
	try {
		processor.sound_processing();
	}
	catch (sound_processor_exception e) {
		cerr << e.what();
		cerr << "Error in sound processing\n";
		return -1;
	}

	/*sound_header sh;
	wav_reader test;
	test.open("music/output.wav");
	test >> sh;
	cout << string(sh);
	return 0;*/
}
