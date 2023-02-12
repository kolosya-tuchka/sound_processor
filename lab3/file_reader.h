#pragma once
#include <fstream>
#include <string>

using namespace std;

class file_reader
{
public:
	file_reader();
	file_reader(string file_path);
	~file_reader();

	void open(string file_path);
	void open();
	void close();

	template <typename data_type>
	void operator>>(data_type& out) {
		input >> out;
	}

	operator bool();

	void get_line(string& out);

	string file_path;

private:
	ifstream input;
};

