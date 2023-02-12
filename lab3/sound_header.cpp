#include "sound_header.h"
#include "wav_reader.h"
#include "wav_writer.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

sound_header::sound_header() {
	primary_file_len = 0;
	channels = 1;
	freq = 44100;
	depth = 16;
	file_len = 0;
	bytes_per_sec = freq * depth / 8;
	bytes_per_sample = SHRT_MAX;
}

sound_header::sound_header(const sound_header& other) {
	*this = other;
}

sound_header& sound_header::operator=(const sound_header& other) {
	if (this == &other) {
		return *this;
	}

	this->primary_file_len = other.primary_file_len;
	this->channels = other.channels;
	this->freq = other.freq;
	this->depth = other.depth;
	this->file_len = other.file_len;
	this->bytes_per_sec = other.bytes_per_sec;
	this->bytes_per_sample = other.bytes_per_sample;

	return *this;
}

bool sound_header::operator==(const sound_header& other) const {
	return this->depth == other.depth &&
		this->channels == other.channels &&
		this->freq == other.freq;
}

sound_header::operator string() const {
	return "Primary file len: " + to_string(primary_file_len)
		+ "\nChannels: " + to_string(channels)
		+ "\nFrequency: " + to_string(freq)
		+ "\nBytes per sec: " + to_string(bytes_per_sec)
		+ "\nBytes per sample: " + to_string(bytes_per_sample)
		+ "\nDepth: " + to_string(depth)
		+ "\nFile length: " + to_string(file_len) + "\n";
}

wav_writer& operator<<(wav_writer& os, sound_header& sh) {
	os << sh.riff;
	os << sh.primary_file_len;
	os << sh.wave;
	os << sh.fmt;
	os << sh.pcm;
	os << sh.audio_format;
	os << sh.channels;
	os << sh.freq;
	os << sh.bytes_per_sec;
	os << sh.bytes_per_sample;
	os << sh.depth;
	os << sh.data_str;
	os << sh.file_len;
	return os;
}

wav_reader& operator>>(wav_reader& is, sound_header& sh) {
	is.ignore(4);
	is >> sh.primary_file_len;
	is.ignore(14);
	is >> sh.channels;
	is >> sh.freq;
	is >> sh.bytes_per_sec;
	is >> sh.bytes_per_sample;
	is >> sh.depth;
	is.ignore(4);
	is >> sh.file_len;
	return is;
}