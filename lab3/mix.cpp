#include "mix.h"
#include "mix_flag_safe.h"
#include "mix_flag_concate.h"
#include "soundp_command_argument_exception.h"
#include "soundp_file_exception.h"

mix::mix() : base_command_with_options<sound_processor, mix>("Mixes two tracks.\nFlags:\n -s - to mix without short int overflow;\n -c - to concate tracks if second is longer.") { add_options(); }

mix::mix(string info) : base_command_with_options<sound_processor, mix>(info) { add_options(); }

short mix::mix_signals(short first, short second)
{
	if (safe_mode) {
		return (first / 2) + (second / 2);
	}
	else {
		int out = first + second;
		return clamp(out, SHRT_MIN, SHRT_MAX);
	}
}

void mix::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() < 2) {
		throw soundp_command_argument_exception("Expected 2 arguments\n");
	}
	if (args[0][0] != '$') {
		throw soundp_command_argument_exception("Expected $\n");
	}
	string file_ind = args[0].substr(1, args[0].size() - 1);
	int index = 0;
	float seconds;
	try {
		string_util::parse_int(file_ind.c_str(), index);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}
	try {
		string_util::parse_float(args[1].c_str(), seconds);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}

	string file;
	try {
		obj.get_input_file(--index, file);
	}
	catch (soundp_file_exception e) {
		cerr << e.what();
		throw soundp_file_exception("Error getting input file\n");
	}

	int i = 2;

	if (args.size() > i && args[i][0] != '-') {
		throw soundp_command_argument_exception("Expected 2 arguments\n");
	}

	while (i < args.size()) {
		vector<string> temp;
		temp.push_back(args[i++]);
		while (i < args.size() && args[i][0] != '-') {
			temp.push_back(args[i++]);
		}
		try {
			additional_command_manager.exec_command(*this, temp);
		}
		catch (sound_processor_exception e) {
			cerr << e.what();
			throw soundp_command_exception("Error in command " + temp[0] + "\n");
		}
	}

	wav_reader first;
	first.open(obj.output_file);
	wav_reader second;
	second.open(file);
	wav_writer temp;
	temp.open("temp.wav");

	sound_header sh1, sh2;
	first >> sh1;
	second >> sh2;
	seconds = clamp(seconds, 0.0f, (float)(sh1.file_len / sh1.bytes_per_sec));
	
	int pos_first = obj.header_size + sh1.bytes_per_sec * seconds;
	sound_header sh_out = sh1;
	sh_out.primary_file_len = ((sh1.primary_file_len - pos_first) < sh2.primary_file_len) && concate ? pos_first + sh2.file_len : sh1.primary_file_len;
	sh_out.file_len = sh_out.primary_file_len - obj.header_size;

	temp << sh_out;
	
	for (int i = 0; i < sh1.freq * seconds; ++i) {
		short signal;
		first >> signal;
		temp << signal;
	}

	while (first) {
		short sig1, sig2 = 0;
		first >> sig1;
		if (second) {
			second >> sig2;
		}
		temp << mix_signals(sig1, sig2);
	}
	if (concate) {
		while (second) {
			short signal;
			second >> signal;
			temp << signal;
		}
	}

	first.close();
	second.close();
	temp.close();

	remove(obj.output_file.c_str());
	int status = rename("temp.wav", obj.output_file.c_str());
}

void mix::add_options()
{
    additional_command_manager.add_command("-s", new mix_flag_safe());
    additional_command_manager.add_command("-c", new mix_flag_concate());
}
