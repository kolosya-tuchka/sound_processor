#pragma once

#include <string>
#include "wav_reader.h"
#include "wav_writer.h"

using namespace std;

class sound_header {
public:
	string riff = "RIFF";
	unsigned int primary_file_len;
	const string wave = "WAVE";
	const string fmt = "fmt ";
	const int pcm = 16;
	const short int audio_format = 1;
	short int channels;
	unsigned int freq;
	unsigned int bytes_per_sec;
	unsigned short int bytes_per_sample;
	unsigned short int depth;
	const string data_str = "data";
	unsigned int file_len;

	sound_header();
	sound_header(const sound_header& other);

	operator string() const;
	sound_header& operator=(const sound_header& other);
	bool operator==(const sound_header& other) const;

	friend wav_writer& operator<<(wav_writer& os, sound_header& sh);
	friend wav_reader& operator>>(wav_reader& is, sound_header& sh);
};