#pragma once
#include <string>
#include <map>
#include "base_command.h"
#include "string_util.h"
#include <iostream>
#include "soundp_command_argument_exception.h"
#include "soundp_file_exception.h"
#include <exception>

using namespace std;

template <class obj_type>
class command_manager
{
public:
	command_manager<obj_type>() {

	}
	~command_manager<obj_type>() {
		for (auto const& comm : commands) {
			delete comm.second;
		}
	}

	void add_command(string command_name, base_command<obj_type>* new_command) {
		commands[command_name] = new_command;
	}

	void exec_command(obj_type& obj, vector<string> command) {
		if (command.size() == 0) {
			throw soundp_command_exception("Command request is empty\n");
		}

		string comm_name = command[0];
		command.erase(command.begin(), command.begin() + 1);

		if (commands.find(comm_name) == commands.end()) {
			throw soundp_command_exception("Error: no such command: " + comm_name + ".Type help to see the list of commands\n");
		}

		try {
			commands[comm_name]->exec(obj, command);
		}
		catch (sound_processor_exception e) {
			cerr << e.what();
			throw soundp_command_exception("Error in command: " + comm_name + "\n");
		}
	}

	void exec_command(obj_type& obj, string command) {
		vector<string> temp = string_util::split(command);
		try {
			exec_command(obj, temp);
		}
		catch (sound_processor_exception e) {
			throw soundp_command_exception(e.what());
		}
	}

	map<string, string> get_info() {
		map<string, string> result;
		for (const auto& comm : commands) {
			result[comm.first] = comm.second->get_info();
		}
		return result;
	}
private:
	map<string, base_command<obj_type>*> commands;
};

