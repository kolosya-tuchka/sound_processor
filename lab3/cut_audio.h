#pragma once
#include "base_command.h"
#include "sound_processor.h"

class cut_audio : public base_command<sound_processor>
{
public:
	cut_audio();
	cut_audio(string info);

	virtual void exec(sound_processor& obj, vector<string> args) override;
};

