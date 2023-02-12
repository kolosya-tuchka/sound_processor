#pragma once
#include "sound_processor_exception.h"
class soundp_command_exception : public sound_processor_exception
{
public:
	soundp_command_exception(string info = "Error in command");
};

