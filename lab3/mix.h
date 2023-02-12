#pragma once
#include "base_command_with_options.h"
#include "sound_processor.h"
#include "sound_header.h"
#include "wav_reader.h"
#include "wav_writer.h"
#include <algorithm>
#include <iostream>

using namespace std;

class mix : public base_command_with_options<sound_processor, mix>
{
public:
	mix();
	mix(string info);

	short mix_signals(short first, short second);
	virtual void exec(sound_processor& obj, vector<string> args) override;

	bool concate = false, safe_mode = false;

protected:
	virtual void add_options() override;
};

