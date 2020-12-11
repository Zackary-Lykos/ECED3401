#pragma once
#ifndef _WAVEHEADER_H_
#define _WAVEHEADER_H_

#include <iostream>

typedef struct header
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;
} header;

class WaveHeader
{
private:
	header tempheader;
	int samples_per_channel;
	int bytes_per_sample;
	int number_of_channels;
	int number_of_samples;
public:
	//    WaveHeader(); //¿´Çé¿öÉ¾³ı
	//    WaveHeader(header);
	//    WaveHeader(class WaveHeader& header);
	int set_samples_per_channel(int);
	int set_bytes_per_sample(int);
	int set_number_of_channels(int);
	int set_number_of_samples(int);
	int set_header(header aheader);
	int set_sample_rate(int);

	int get_samples_per_channel();
	int get_bytes_per_sample();
	int get_number_of_channels();
	int get_number_of_samples();
	int get_sample_rate();
	int print_header(void);
	header* get_header();
};

#endif
