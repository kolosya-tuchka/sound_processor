#include "concate_flag_backwards.h"
#include "soundp_command_argument_exception.h"

void concate_flag_backwards::exec(concate& obj, vector<string> args)
{
    if (args.size() != 0) {
        throw soundp_command_argument_exception("Expected 0 arguments\n");
    }
    obj.backwards = true;
}
