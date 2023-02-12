#include "set_output_file.h"
#include "soundp_file_exception.h"
#include "soundp_command_argument_exception.h"

set_output_file::set_output_file() : base_command<sound_processor>() {}

void set_output_file::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() != 1) {
		throw soundp_command_argument_exception("Expected 1 argument\n");
	}

	obj.output_file = args[0];
	string in;
	try {
		obj.get_input_file(0, in);
	}
	catch(soundp_file_exception e) {
		cerr << e.what();
		throw soundp_file_exception("Error setting output file\n");
	}

	try {
		obj.private_com_manager.exec_command(obj, "copy_audio " + in + " " + obj.output_file);
	}
	catch (sound_processor_exception e) {
		cerr << e.what();
		throw soundp_command_exception("Error in command copy_audio\n");
	}
}

