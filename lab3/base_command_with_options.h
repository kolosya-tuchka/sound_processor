#pragma once
#include "base_command.h"
#include "command_manager.h"

template <typename obj_type, typename additional_type>
class base_command_with_options : public base_command<obj_type>
{
public:
	base_command_with_options() : base_command<obj_type>(){}
	base_command_with_options(string info) : base_command<obj_type>(info){}
protected:
	virtual void add_options() = 0;
	command_manager<obj_type> option_command_manager;
	command_manager<additional_type> additional_command_manager;
};

