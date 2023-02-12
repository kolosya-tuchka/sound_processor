#pragma once
#include <vector>
#include "base_command_with_options.h"
#include "sound_processor.h"
#include "sound_header.h"

class init_sound_processor : public base_command_with_options<sound_processor, sound_processor>
{
public:
	init_sound_processor();
	virtual void exec(sound_processor& obj, vector<string> args) override;
protected:
	virtual void add_options() override;
};