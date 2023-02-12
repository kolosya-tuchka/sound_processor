#include "sound_processor_exception.h"

sound_processor_exception::sound_processor_exception(string info)
{
    this->info = info;
}

string sound_processor_exception::what()
{
    return info;
}
