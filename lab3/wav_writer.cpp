#include "wav_writer.h"

wav_writer::wav_writer()
{
}

wav_writer::wav_writer(string file_path)
{
	this->file_path = file_path;
}

wav_writer::~wav_writer()
{
	close();
}

void wav_writer::open(string file_path, ios_base::openmode mode)
{
	this->file_path = file_path;
	open(mode);
}

void wav_writer::open(ios_base::openmode mode)
{
	audio.open(file_path, mode);
}

void wav_writer::close()
{
	dump_buffer();
	audio.close();
}

void wav_writer::seek(int bytes, ios_base::seekdir way)
{
	audio.seekp(bytes, way);
}

void wav_writer::operator<<(char data)
{
	add_to_buf(1, &data);
}

void wav_writer::operator<<(short int data)
{
	char temp[2];
	encode(data, 2, temp);
	add_to_buf(2, temp);
}

void wav_writer::operator<<(unsigned short int data)
{
	char temp[2];
	encode(data, 2, temp);
	add_to_buf(2, temp);
}

void wav_writer::operator<<(int data)
{
	char temp[4];
	encode(data, 4, temp);
	add_to_buf(4, temp);
}

void wav_writer::operator<<(unsigned int data)
{
	char temp[4];
	encode(data, 4, temp);
	add_to_buf(4, temp);
}

void wav_writer::operator<<(string data)
{
	add_to_buf(data.size(), data.c_str());
}

wav_writer::operator bool()
{
	return audio.good();
}

void wav_writer::add_to_buf(int bytes, const char* in)
{
	int counter = 0;
	
	while (counter < bytes) {
		if (cur_byte >= buf_size) {
			dump_buffer();
			continue;
		}
		buffer[cur_byte++] = in[counter++];
	}
}

void wav_writer::dump_buffer()
{
	audio.write(buffer, cur_byte);
	cur_byte = 0;
}
