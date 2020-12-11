#include "WaveHeader.h"

int WaveHeader::set_header(header aheader)
{
	for (int i = 0; i < 4; i++)
	{
		tempheader.chunk_id[i] = aheader.chunk_id[i];
		tempheader.format[i] = aheader.format[i];
		tempheader.subchunk1_id[i] = aheader.subchunk1_id[i];
		tempheader.subchunk2_id[i] = aheader.subchunk2_id[i];
	}

	tempheader.chunk_size = aheader.chunk_size;
	tempheader.subchunk1_size = aheader.subchunk1_size;
	tempheader.audio_format = aheader.audio_format;
	tempheader.num_channels = aheader.num_channels;
	tempheader.sample_rate = aheader.sample_rate;
	tempheader.byte_rate = aheader.byte_rate;
	tempheader.block_align = aheader.block_align;
	tempheader.bits_per_sample = aheader.bits_per_sample;
	tempheader.subchunk2_size = aheader.subchunk2_size;
	printf("pass Waveheader set_header\n");
	return 0;
}

int WaveHeader::get_samples_per_channel()
{
	samples_per_channel = tempheader.subchunk2_size / 2 / tempheader.num_channels;
	return samples_per_channel;
}

int WaveHeader::get_bytes_per_sample()
{
	bytes_per_sample = tempheader.bits_per_sample / 8;
	return bytes_per_sample;
}

int WaveHeader::get_number_of_channels()
{
	number_of_channels = tempheader.num_channels;
	return number_of_channels;
}

int WaveHeader::get_number_of_samples() 
{
	number_of_samples = tempheader.subchunk2_size * 8 / tempheader.bits_per_sample;
	return number_of_samples;
}

int WaveHeader::get_sample_rate()
{
	return tempheader.sample_rate;
}

/*header* WaveHeader::get_header()
{
	//no time to finish this part
}*/

int WaveHeader::set_samples_per_channel(int i)
{
	samples_per_channel = i;
	return i;
}

int WaveHeader::set_bytes_per_sample(int i)
{
	bytes_per_sample = i;
	return i;
}

int WaveHeader::set_number_of_channels(int i)
{
	number_of_channels = i;
	return i;
}

int WaveHeader::set_number_of_samples(int i)
{
	number_of_samples = i;
	return i;
}

int WaveHeader::set_sample_rate(int i)
{
	tempheader.sample_rate = i;
	return i;
}