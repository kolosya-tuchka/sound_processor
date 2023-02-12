#pragma once
#include "concate.h"
#include "base_command.h"

class concate_flag_backwards : public base_command<concate>
{
public:
	virtual void exec(concate& obj, vector<string> args) override;
};

