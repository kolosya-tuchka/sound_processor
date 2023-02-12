#include "file_reader.h"
#include <fstream>
#include <string>

using namespace std;

file_reader::file_reader()
{
}

file_reader::file_reader(string file_path)
{
	this->file_path = file_path;
}

file_reader::~file_reader()
{
	input.close();
}

void file_reader::open(string file_path)
{
	this->file_path = file_path;
	open();
}

void file_reader::open()
{
	input.open(file_path);
}

void file_reader::close()
{
	input.close();
}

file_reader::operator bool()
{
	return input.good();
}

void file_reader::get_line(string& out)
{
	getline(input, out);
}
