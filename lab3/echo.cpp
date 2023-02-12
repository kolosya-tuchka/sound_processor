#include "echo.h"
#include <algorithm>

echo::echo() : base_command<sound_processor>("Makes echo $2 times every $3 seconds from $1 second of the track. 4th and 5th arguments are optional and they are for echo multiplyer and cutting echo track. 4th argument should be 0-1 float number") {}

echo::echo(string info) : base_command<sound_processor> (info) {}

void echo::exec(sound_processor& obj, vector<string> args)
{
	if (args.size() != 3 && args.size() != 4 && args.size() != 5) {
		throw soundp_command_argument_exception("Expected 3 or 4 or 5 arguments\n");
	}

	float start;
	int times;
	float seconds;
	float end = 100000 - 1;
	float echo_mul = 0.6f;

	try {
		string_util::parse_float(args[0].c_str(), start);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}

	try {
		string_util::parse_int(args[1].c_str(), times);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}

	try {
		string_util::parse_float(args[2].c_str(), seconds);
	}
	catch (invalid_argument e) {
		throw soundp_command_argument_exception("Invalid argument\n");
	}

	if (args.size() >= 4) {
		try {
			string_util::parse_float(args[3].c_str(), echo_mul);
		}
		catch (invalid_argument e) {
			throw soundp_command_argument_exception("Invalid argument\n");
		}
	}

	if (args.size() == 5) {
		try {
			string_util::parse_float(args[4].c_str(), end);
		}
		catch (invalid_argument e) {
			throw soundp_command_argument_exception("Invalid argument\n");
		}
	}

	echo_mul = clamp(echo_mul, 0.0f, 1.0f);

	try {
		obj.private_com_manager.exec_command(obj, "copy_audio " + obj.output_file + " temp_echo.wav");
		obj.add_input_file("temp_echo.wav");
		int index = obj.input_files_size();
		
		string prev_out = obj.output_file;
		obj.output_file = "temp_echo.wav";

		if (start > 0) {
			obj.com_manager.exec_command(obj, "cut 0 " + to_string(start));
		}
		obj.com_manager.exec_command(obj, "cut " + to_string(end) + " " + to_string(100000));

		float cur_begin = start + seconds;
		float cur_echo_mul = echo_mul;
		for (float i = 0; i < times; ++i, cur_begin += seconds, cur_echo_mul *= echo_mul) {
			obj.output_file = "temp_echo.wav";
			obj.com_manager.exec_command(obj, "volume " + to_string(cur_echo_mul));
			obj.output_file = prev_out;
			obj.com_manager.exec_command(obj, "mix $" + to_string(index) + " " + to_string(cur_begin) + " -c");
		}
	}
	catch (sound_processor_exception e) {
		throw sound_processor_exception(e.what());
	}

	obj.pop_input_files();
	remove("temp_echo.wav");
}
