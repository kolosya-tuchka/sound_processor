#include "wav_reader.h"

wav_reader::wav_reader()
{
}

wav_reader::wav_reader(string file_path)
{
	this->file_path = file_path;
	open(file_path);
}

wav_reader::~wav_reader()
{
	close();
}

void wav_reader::open(string file_path)
{
	this->file_path = file_path;
	open();
}

void wav_reader::open()
{
	input.open(file_path, ios::binary);
}

void wav_reader::close()
{
	input.close();
}

void wav_reader::ignore(unsigned int count)
{
	cur_byte += count;
}

void wav_reader::seek(int bytes, ios_base::seekdir way)
{
	//input.seekg(bytes, way);
}

void wav_reader::operator>>(short& out)
{
	char temp[2];
	get_from_buf(2, temp);
	decode(temp, 2, out);
}

void wav_reader::operator>>(unsigned int& out)
{
	char temp[4];
	get_from_buf(4, temp);
	decode(temp, 4, out);
}

void wav_reader::operator>>(int& out)
{
	char temp[4];
	get_from_buf(4, temp);
	decode(temp, 4, out);
}

void wav_reader::operator>>(unsigned short& out)
{
	char temp[2];
	get_from_buf(2, temp);
	decode(temp, 2, out);
}

wav_reader::operator bool()
{
	return (input.good() || cur_byte < cur_buf_size);
}

void wav_reader::get_from_buf(int bytes, char* out)
{
	int counter = 0;

	while (counter < bytes) {
		if (cur_byte >= cur_buf_size) {
			if (!input) {
				return;
			}
			load_buffer();
			continue;
		}
		out[counter++] = buffer[cur_byte++];
	}
}

void wav_reader::load_buffer()
{
	cur_byte %= cur_buf_size;
	input.read(buffer, buf_size);
	cur_buf_size = input.gcount();
}
