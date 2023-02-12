#pragma once
#include <string>

using namespace std;

class sound_processor_exception
{
public:
	sound_processor_exception(string info = "Error in sound processing");
	virtual string what();
protected:
	string info;
};

