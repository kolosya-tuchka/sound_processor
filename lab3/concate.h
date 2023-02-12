#pragma once
#include "sound_processor.h"
#include "base_command_with_options.h"

class concate : public base_command_with_options<sound_processor, concate>
{
public:
	concate();
	concate(string info);

	virtual void exec(sound_processor& obj, vector<string> args) override;

	bool backwards = false;

protected:
	virtual void add_options() override;
};

