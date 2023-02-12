#include "concate.h"
#include "concate_flag_backwards.h"
#include "soundp_command_argument_exception.h"
#include "soundp_file_exception.h"
#include <algorithm>

concate::concate() : base_command_with_options<sound_processor, concate>("Concates two tracks.\nFlags:\n-b - concate backwards.") { add_options(); }

concate::concate(string info) : base_command_with_options<sound_processor, concate>(info) { add_options(); }

void concate::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() < 1 || (args.size() > 1 && args[1][0] != '-')) {
		throw soundp_command_argument_exception("Expected 1 argument\n");
	}
	if (args[0][0] != '$') {
		throw soundp_command_argument_exception("Expected $\n");
	}
	string file_ind = args[0].substr(1, args[0].size() - 1);
	int index;
	try {
		string_util::parse_int(file_ind.c_str(), index);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}
	string file;
	try {
		obj.get_input_file(--index, file);
	}
	catch (soundp_file_exception e) {
		throw soundp_file_exception("Error getting input file\n");
	}

	int i = 1;
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
			throw soundp_command_exception("Error executing command " + temp[0] + "\n");
		}
	}

	wav_reader first;
	wav_reader second;
	if (backwards) {
		first.open(file);
		second.open(obj.output_file);
	}
	else {
		first.open(obj.output_file);
		second.open(file);
	}

	wav_writer temp;
	temp.open("temp.wav");

	sound_header sh1, sh2;
	first >> sh1;
	second >> sh2;

	sound_header sh_out = sh1;
	sh_out.primary_file_len = obj.header_size + sh1.file_len + sh2.file_len;
	sh_out.file_len = sh_out.primary_file_len - obj.header_size;

	temp << sh_out;

	while (first) {
		short signal;
		first >> signal;
		temp << signal;
	}
	while (second) {
		short signal;
		second >> signal;
		temp << signal;
	}

	first.close();
	second.close();
	temp.close();

	remove(obj.output_file.c_str());
	int status = rename("temp.wav", obj.output_file.c_str());
}

void concate::add_options()
{
	additional_command_manager.add_command("-b", new concate_flag_backwards());
}
