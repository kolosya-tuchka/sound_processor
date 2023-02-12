#pragma once
#include "soundp_command_exception.h"
class soundp_command_argument_exception : public soundp_command_exception
{
public:
	soundp_command_argument_exception(string info = "Error in command with argument");
};

