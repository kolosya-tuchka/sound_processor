#pragma once
#include "base_command.h"
#include "sound_processor.h"

class load_config : public base_command<sound_processor>
{
public:
	virtual void exec(sound_processor& obj, vector<string> args) override;
};

