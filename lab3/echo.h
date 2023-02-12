#pragma once
#include "sound_processor.h"
#include "base_command.h"

class echo : public base_command<sound_processor>
{
public:
	echo();
	echo(string info);

	virtual void exec(sound_processor& obj, vector<string> args) override;
};

