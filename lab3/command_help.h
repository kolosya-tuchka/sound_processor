#pragma once
#include "base_command.h"
#include "sound_processor.h"

class command_help : public base_command<sound_processor>
{
public:
	command_help();
	command_help(string info);
	virtual void exec(sound_processor& obj, vector<string> args) override;
};

