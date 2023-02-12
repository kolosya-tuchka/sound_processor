#include "cut_audio.h"
#include "soundp_command_argument_exception.h"
#include <algorithm>

cut_audio::cut_audio() : base_command<sound_processor>("Cuts track") {}

cut_audio::cut_audio(string info) : base_command<sound_processor>(info) {}

void cut_audio::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() != 2) {
		throw soundp_command_argument_exception("Expected 2 arguments\n");
	}
	float from, to;
	try {
		string_util::parse_float(args[0].c_str(), from);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}
	try {
		string_util::parse_float(args[1].c_str(), to);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}
	if (from >= to) {
		throw soundp_command_argument_exception("First argument must be less than second\n");
	}
	wav_reader audio;
	audio.open(obj.output_file);
	wav_writer temp;
	temp.open("temp.wav");

	sound_header sh;
	audio >> sh;

	from = clamp(from, 0.0f, (float)(sh.file_len / sh.bytes_per_sec));
	to = clamp(to, 0.0f, (float)(sh.file_len / sh.bytes_per_sec));
	int pos_from = from * obj.valid_header.freq, pos_to = to * obj.valid_header.freq;

	sh.primary_file_len -= (to - from) * sh.bytes_per_sec;
	sh.file_len = sh.primary_file_len - obj.header_size;
	temp << sh;

	int pos = 0;
	while (audio) {
		short signal;
		audio >> signal;
		if (pos < pos_from || pos > pos_to) {
			temp << signal;
		}
		pos++;
	}

	audio.close();
	temp.close();

	remove(obj.output_file.c_str());
	int status = rename("temp.wav", obj.output_file.c_str());
}
