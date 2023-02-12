#include "init_sound_processor.h"
#include "command_help.h"
#include "set_output_file.h"
#include "load_config.h"
#include "soundp_command_argument_exception.h"
#include "soundp_file_exception.h"
#include <exception>

init_sound_processor::init_sound_processor() : base_command_with_options<sound_processor, sound_processor>()
{
	add_options();
}

void init_sound_processor::exec(sound_processor& obj, vector<string> args)
{
	int i = 0, size = args.size();
	while (i < size) {
		if (args[i][0] == '-') {
			break;
		}
		try {
			obj.add_input_file(args[i++]);
		} catch (soundp_file_exception e) {
			cerr << e.what();
			throw soundp_file_exception("Error adding input file\n");
		}
	}

	if (i == 0) {
		throw soundp_command_argument_exception("No input files\n");
	}

	while (i < size) {
		vector<string> temp;
		temp.push_back(args[i++]);
		while (i < size && args[i][0] != '-') {
			temp.push_back(args[i++]);
		}
		try {
			option_command_manager.exec_command(obj, temp);
		}
		catch (sound_processor_exception e) {
			cerr << e.what();
			throw soundp_command_exception("Error in command: " + temp[0] + "\n");
		}
	}

	if (obj.output_file == "") {
		throw soundp_file_exception("No output file\n");
	}
	if (obj.config.file_path == "") {
		throw soundp_file_exception("No config file\n");
	}
}

void init_sound_processor::add_options()
{
	option_command_manager.add_command("-h", new command_help());
	option_command_manager.add_command("-o", new set_output_file());
	option_command_manager.add_command("-c", new load_config());
}
