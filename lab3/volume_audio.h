#pragma once
#include "sound_processor.h"

class volume_audio : public base_command<sound_processor>
{
public:
	volume_audio();
	volume_audio(string info);

	virtual void exec(sound_processor& obj, vector<string> args) override;
};

