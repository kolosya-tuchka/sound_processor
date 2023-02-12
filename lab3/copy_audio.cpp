#include "copy_audio.h"
#include "soundp_command_argument_exception.h"
#include "soundp_file_exception.h"

void copy_audio::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() < 2) {
		throw soundp_command_argument_exception("Expected 2 arguments\n");
	}

	wav_reader in;
	in.open(args[0]);

	if (!in) {
		throw soundp_file_exception("File " + args[0] + " does not exist\n");
	}

	wav_writer out;
	out.open(args[1]);

	sound_header sh;
	in >> sh;
	out << sh;

	while (in) {
		short temp;
		in >> temp;
		out << temp;
	}
}
