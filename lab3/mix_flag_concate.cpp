#include "mix_flag_concate.h"
#include "soundp_command_argument_exception.h"

void mix_flag_concate::exec(mix& obj, vector<string> args)
{
    if (args.size() != 0) {
        throw soundp_command_argument_exception("Expected 0 arguments\n");
    }
    obj.concate = true;
}
