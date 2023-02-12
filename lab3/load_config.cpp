#include "load_config.h"
#include "soundp_command_argument_exception.h"

void load_config::exec(sound_processor& obj, vector<string> args)
{
    if (args.size() != 1) {
        throw soundp_command_argument_exception("Expected 1 argument\n");
    }

    obj.config.file_path = args[0];
}
