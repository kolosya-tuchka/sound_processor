#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class wav_reader
{
public:
	wav_reader();
	wav_reader(string file_path);
	~wav_reader();

	void open(string file_path);
	void open();
	void close();
	void ignore(unsigned int count);
	void seek(int bytes, ios_base::seekdir way = ios_base::beg);

	void operator>>(short& out);
	void operator>>(unsigned int& out);
	void operator>>(int& out);
	void operator>>(unsigned short& out);

	template <typename data_type>
	void decode(char* data, int byte_size, data_type& out) {
		out = 0;
		for (int i = 0; i < byte_size; ++i) {
			for (int j = 0; j < 8; ++j) {
				data_type num = data[i] & (1 << j);
				out += num == 0 ? 0 : (1 << (i * 8 + j));
			}
		}
	}

	operator bool();

	string file_path;

private:
	void get_from_buf(int bytes, char* out);
	void load_buffer();

	static const int buf_size = 100000;
	int cur_byte = buf_size;
	int cur_buf_size = buf_size;
	char buffer[buf_size];
	ifstream input;
};

