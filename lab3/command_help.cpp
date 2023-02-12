#include "command_help.h"
#include "soundp_command_argument_exception.h"

command_help::command_help() : base_command<sound_processor>("Prints info about each command") {}

command_help::command_help(string info) : base_command<sound_processor>(info) {}

void command_help::exec(sound_processor& obj, vector<string> args)
{
    if (args.size() != 0) {
        throw soundp_command_argument_exception("Expected 0 arguments\n");
    }

    map<string, string> info = obj.com_manager.get_info();
    for (const auto& it : info) {
        cout << it.first << " - " << it.second << endl;
    }
}
