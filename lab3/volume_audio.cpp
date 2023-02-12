#include "volume_audio.h"
#include <algorithm>

volume_audio::volume_audio() : base_command<sound_processor>("Changes volume of the sound. It takes 1 or 3 arguments.") {}

volume_audio::volume_audio(string info) : base_command<sound_processor>(info) {}

void volume_audio::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() != 1 && args.size() != 3) {
		throw soundp_command_argument_exception("Expected 1 or 2 arguments\n");
	}

	wav_reader audio;
	audio.open(obj.output_file);
	wav_writer temp;
	temp.open("temp.wav");

	sound_header sh;
	audio >> sh;
	temp << sh;

	float vol_mul;
	try {
		string_util::parse_float(args[0].c_str(), vol_mul);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}

	float from = -1, to = INT_MAX;
	if (args.size() == 3) {
		try {
			string_util::parse_float(args[1].c_str(), from);
		}
		catch (invalid_argument e) {
			throw soundp_command_argument_exception("Invalid argument\n");
		}
		try {
			string_util::parse_float(args[2].c_str(), to);
		}
		catch (invalid_argument e) {
			throw soundp_command_argument_exception("Invalid argument\n");
		}
		if (from >= to) {
			throw soundp_command_argument_exception("Second argument must be less than third\n");
		}
		from = clamp((float)from, 0.0f, (float)(sh.file_len / sh.bytes_per_sec));
		to = clamp((float)to, 0.0f, (float)(sh.file_len / sh.bytes_per_sec));
	}

	long long pos_from = from * obj.valid_header.freq, pos_to = to * obj.valid_header.freq;

	long long pos = 0;
	while (audio) {
		short signal;
		audio >> signal;
		if (pos >= pos_from && pos <= pos_to) {
			temp << clamp((short)(signal * vol_mul), (short)SHRT_MIN, (short)SHRT_MAX);
		}
		else {
			temp << signal;
		}
		pos++;
	}

	audio.close();
	temp.close();

	remove(obj.output_file.c_str());
	int status = rename("temp.wav", obj.output_file.c_str());
}
