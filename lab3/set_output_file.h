#pragma once
#include "sound_processor.h"
#include "base_command.h"

class set_output_file : public base_command<sound_processor>
{
public:
	set_output_file();
	virtual void exec(sound_processor& obj, vector<string> args) override;
};

