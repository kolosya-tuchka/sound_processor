#pragma once
#include "base_command.h"
#include "mix.h"

class mix_flag_safe : public base_command<mix>
{
public:
	virtual void exec(mix& obj, vector<string> args) override;
};

