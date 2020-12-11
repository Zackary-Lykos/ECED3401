#include "Channel.h"
int length;
Channel::Channel(void)
{
	data_length = 0;
	channel_data = 0;
}
Channel::Channel(Channel* newchannel)
{
	data_length = newchannel->get_length();
	channel_data = new int[length];
	for (int i = 0; i < length; i++)
	{
		channel_data[i] = newchannel->get_sample(i);
	}
}
Channel::Channel(int* array, int length)
{
	data_length = get_length();
	channel_data = new int[length];
	for (int i = 0; i < length; i++)
	{
		channel_data[i] = array[i];
	}
}
int Channel::get_length()
{
	return length;
}
int Channel::set_length(int data_length)
{
	length = data_length;
	return 0;
}
int Channel::get_sample(int i)
{
	return channel_data[i];
}