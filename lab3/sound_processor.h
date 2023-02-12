#pragma once
#include <string>
#include "command_manager.h"
#include "sound_header.h"
#include <vector>
#include "file_reader.h"
#include "wav_reader.h"
#include "wav_writer.h"

using namespace std;

class sound_processor
{
public:
	sound_processor();
	sound_processor(int argc, char** argv);
	sound_processor(string request);

	void sound_processing();
	void get_input_file(int index, string& out);
	void add_input_file(string file);
	void pop_input_files();
	int input_files_size();

	file_reader config;
	sound_header valid_header;
	command_manager<sound_processor> com_manager, private_com_manager;
	
	string output_file;
	const int header_size = 42;

private:
	string request;
	vector<string> input_files;

	string read_command();
	void add_default_commands();
	void default_valid_header();
};
