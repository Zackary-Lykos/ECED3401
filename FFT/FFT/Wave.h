#pragma once
#ifndef _WAVE_H_
#define _WAVE_H_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "WaveHeader.h"
#include "Channel.h"


using namespace std;

class Wave
{
private:
	WaveHeader tempheader;
	char* data;
	Channel** channels;
	int numberOfSamples;
public:
	Wave();
	Wave(WaveHeader, Channel**);
	int wavereader(string);
	int wavewriter(string);
	int print_header(void);
	Wave* stereo_to_mono(void);
	Wave* speed_change(float);
	Channel getChannel();
};
#endif
