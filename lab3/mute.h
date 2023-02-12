#pragma once
#include "base_command.h"
#include "sound_processor.h"

using namespace std;

class mute : public base_command<sound_processor>
{
public:
	mute();
	mute(string info);

	virtual void exec(sound_processor& obj, vector<string> args) override;
};

