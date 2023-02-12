#pragma once
#include <string>
#include <vector>

using namespace std;

template <typename obj_type>
class base_command
{
public:
	base_command(){}
	base_command<obj_type>(string info) {
		this->info = info;
	}
	virtual void exec(obj_type& obj, vector<string> args) = 0;
	virtual const string& get_info() const {
		return info;
	}
protected:
	string info;
};
