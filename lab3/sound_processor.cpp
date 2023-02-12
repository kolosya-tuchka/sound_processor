#include "sound_processor.h"
#include "command_help.h"
#include "init_sound_processor.h"
#include "mute.h"
#include "copy_audio.h"
#include "mix.h"
#include "volume_audio.h"
#include "concate.h"
#include "cut_audio.h"
#include "echo.h"

sound_processor::sound_processor()
{
    default_valid_header();
    add_default_commands();
}

sound_processor::sound_processor(int argc, char** argv)
{
    default_valid_header();
    add_default_commands();
    request = "sound_processor ";
    for (int i = 1; i < argc; ++i) {
        request += argv[i];
        request += " ";
    }
}

sound_processor::sound_processor(string request)
{
    default_valid_header();
    add_default_commands();
    this->request = request;
}

string sound_processor::read_command()
{
    string result;
    config.get_line(result);
    return result;
}

void sound_processor::sound_processing() {
    try {
        private_com_manager.exec_command(*this, request);
    } 
    catch (sound_processor_exception e) {
        cerr << e.what();
        throw soundp_command_exception("Error in sound processor init\n");
    }

    config.open(config.file_path);
    int line = 0;
    while (config) {
        ++line;
        string command = read_command();
        vector<string> split_com = string_util::split(command);
        if (split_com.size() == 0 || split_com[0][0] == '#') {
            continue;
        }
        try {
            com_manager.exec_command(*this, command);
        }
        catch (sound_processor_exception e) {
            cerr << e.what();
            throw soundp_command_exception("Error executing command: " + command + " in line " + to_string(line) + "\n");
        }
    }
}

void sound_processor::get_input_file(int index, string& out)
{
    if (index < 0 || index >= input_files.size()) {
        throw soundp_file_exception("Index out of range\n");
    }
    out = input_files[index];
}

void sound_processor::add_input_file(string file)
{
    if (!string_util::check_file_format(file, ".wav")) {
        throw soundp_file_exception("Invalid format of file: " + file + ". Expected .wav format\n");
    }
    wav_reader test;
    test.open(file);
    if (!test) {
        throw soundp_file_exception("File " + file + " does not exist\n");
    }
    sound_header header;
    test >> header;
    if (header != valid_header) {
        throw soundp_file_exception("Invalid header format of file: " + file + "\n");
    }
    input_files.push_back(file);
}

void sound_processor::pop_input_files()
{
    input_files.pop_back();
}

int sound_processor::input_files_size()
{
    return input_files.size();
}

void sound_processor::add_default_commands() {
    com_manager.add_command("help", new command_help());
    com_manager.add_command("mute", new mute());
    com_manager.add_command("mix", new mix());
    com_manager.add_command("volume", new volume_audio());
    com_manager.add_command("concate", new concate());
    com_manager.add_command("cut", new cut_audio());
    com_manager.add_command("echo", new echo());
    private_com_manager.add_command("sound_processor", new init_sound_processor());
    private_com_manager.add_command("copy_audio", new copy_audio());
}

void sound_processor::default_valid_header()
{
    valid_header.bytes_per_sample = 4;
    valid_header.freq = 44100;
    valid_header.depth = 16;
    valid_header.channels = 1;
}
