#pragma once
#include "sound_processor_exception.h"
class soundp_file_exception : public sound_processor_exception
{
public:
	soundp_file_exception(string info = "Error with file");
};

