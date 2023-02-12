#include "mix_flag_safe.h"
#include "soundp_command_argument_exception.h"

void mix_flag_safe::exec(mix& obj, vector<string> args)
{
    if (args.size() != 0) {
        throw  soundp_command_argument_exception("Expected 0 arguments\n");
    }
    obj.safe_mode = true;
}
