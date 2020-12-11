#pragma once
#include <stdio.h>
#include <iostream>

class Channel
{
private:
	int* channel_data;
	int data_length;
public:
	Channel();
	Channel(Channel*);
	Channel(int*, int);
	int get_length();
	int set_length(int);
	int get_sample(int);
};