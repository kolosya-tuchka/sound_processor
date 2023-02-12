#pragma once
#include <string>
#include <fstream>

using namespace std;

class wav_writer
{
public:
	wav_writer();
	wav_writer(string file_path);
	~wav_writer();

	void open(string file_path, ios_base::openmode mode = ios::binary);
	void open(ios_base::openmode mode = ios::binary);
	void close();
	void seek(int bytes, ios_base::seekdir way = 0);

	void operator<<(char data);
	void operator<<(short int data);
	void operator<<(unsigned short int data);
	void operator<<(int data);
	void operator<<(unsigned int data);
	void operator<<(string data);

	template <typename data_type>
	void encode(data_type data, int byte_size, char* output) {
		memset(output, 0, byte_size);
		for (int i = 0; i < byte_size; ++i) {
			for (int j = 0; j < 8; ++j) {
				data_type temp = (data & (1 << (i * 8 + j)));
				output[i] += temp == 0 ? 0 : (1 << j);
			}
		}
	}

	operator bool();

	string file_path;

private:
	void add_to_buf(int bytes, const char* in);
	void dump_buffer();

	static const int buf_size = 100000;
	int cur_byte = 0;
	char buffer[buf_size];
	ofstream audio;
};