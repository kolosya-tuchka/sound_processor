#pragma once
#include "base_command.h"
#include "sound_processor.h"
#include "wav_reader.h"
#include "wav_writer.h"
#include "sound_header.h"

class copy_audio : public base_command<sound_processor>
{
public:
	virtual void exec(sound_processor& obj, vector<string> args) override;
};

