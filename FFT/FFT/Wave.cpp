#include "Wave.h"
#include "Channel.h"
Wave::Wave(void) //initial system
{
	channels = 0;
}
/*
Wave::Wave(WaveHeader new_header, Channel** newchannels) // create new wave, include format
{
	tempheader = new_header;
	channels = newchannels;
	int thelength;
	int bytes_per_sample;
	bytes_per_sample = tempheader.get_bytes_per_sample();
	int number_of_channels;
	number_of_channels = tempheader.get_number_of_channels();
	int samples_per_channel;
	samples_per_channel = tempheader.get_samples_per_channel();
	thelength =
		tempheader.get_bytes_per_sample() *
		tempheader.get_number_of_channels() *
		tempheader.get_samples_per_channel();
	data = new char[thelength]; //¡ü replace and initial parameters
	char* charpointer;
	charpointer = 0; // data point selection
	short int value;
	int kk;
	kk = 0;
	for (int i = 0; i < samples_per_channel; i++)
	{
		for (int j = 0; j < number_of_channels; j++)
		{
			value = (short int)channels[j]->get_sample(i);
			charpointer = (char*)&value;
			data[kk] = *charpointer;
			charpointer++;
			data[kk + 1] = *charpointer;
			kk = kk + 2;
		}
	}

}*/
int Wave::wavereader(string filename)
{
	header header_buffer; // create header array
	ifstream inputfile;
	inputfile.open(filename, ios::binary);
	inputfile.read((char*)&header_buffer, sizeof(header)); //input header array 
	tempheader.set_header(header_buffer); // transfer butter to internal (tempheader)
	data = new char[tempheader.get_number_of_samples()]; //create data array

	cout << "T1:" << tempheader.get_number_of_samples() << endl;

	inputfile.read(data, tempheader.get_number_of_samples());
	inputfile.close();

	//-----File read finish, start Data seperate

	int* channel_data;
	channel_data = new int[tempheader.get_samples_per_channel()];// create how many samples for 1 channel
	// build 2 Channel array
	channels = new Channel *[tempheader.get_number_of_channels()]; // create two channel
	short int* temp_array;
	temp_array = new short int[tempheader.get_bytes_per_sample() * tempheader.get_samples_per_channel()];
	//create array to store sample data per channel

	char* data_transfer = NULL; //pointer
	int i = 0;
	int j = 0;
	for (i = 0; i < tempheader.get_samples_per_channel(); i++)
	{
		data_transfer = &data[i * tempheader.get_bytes_per_sample()];
		memcpy(&temp_array[i], data_transfer, tempheader.get_bytes_per_sample());//copy all sample to temp array, size 2
	}
	for (i = 0; i < tempheader.get_number_of_channels(); i++) //channel 1, ¡­¡­£» channel 2, ¡­¡­
	{
		for (j = 0; j < tempheader.get_samples_per_channel(); j++)//c1s1, c1s2, c1s3¡­¡­c2s1, c2s2, c3s3
		{
			channel_data[j] = (int)temp_array[2 * j + i];//2 bytes per sample
			cout << channel_data[j] << endl;
		}
		channels[i] = new Channel(channel_data, tempheader.get_samples_per_channel());
		//store c1s* into channel1 in, then start read c2s*
	}
	delete temp_array;
	delete data;
	return 0;
}

//-----Data read finish

	/***************¡ıNot Verified Part, unable to test due to compiler error in previous code¡ı***************/

/*int Wave::wavewriter(std::string filename)
{
	ofstream outputfile;
	outputfile.open(filename, ios::binary | ios::trunc); //set output mode
	header* myheader;
	myheader = tempheader.get_header();
	outputfile.write((char*)myheader, sizeof(header)); //write header data into outputfile

	char* thedata;
	int bytes_per_sample;
	bytes_per_sample = tempheader.get_bytes_per_sample();
	int number_of_channels;
	number_of_channels = tempheader.get_number_of_channels();
	int samples_per_channel;
	samples_per_channel = tempheader.get_samples_per_channel();
	int thelength;
	thelength = number_of_channels * bytes_per_sample * samples_per_channel;

	thedata = new char[thelength];//¡ü replace and initial parameters
	char* pointer;// data point selection
	pointer = 0;
	short int value;
	int k = 0;
	for (int i = 0; i < samples_per_channel; i++)
	{
		for (int j = 0; j < number_of_channels; j++)
		{
			value = (short int)channels[j]->get_sample(i);
			pointer = (char*)&value;
			thedata[k] = *pointer;
			pointer++;
			data[k + 1] = *pointer;
			k = k + 2; // same as in wave::wave
		}
	}
	int size =
		tempheader.get_bytes_per_sample() *
		tempheader.get_number_of_channels() *
		tempheader.get_samples_per_channel(); //calculate output size

	outputfile.write((char*)thedata, size); //output file
	outputfile.close();
	return 0;
}

int Wave::print_header(void)
{
	cout << "number of raw samples=" << tempheader.get_samples_per_channel() * tempheader.get_number_of_channels() << endl;
	cout << "number of channels=" << tempheader.get_number_of_channels() << endl;
	cout << "number of bytes per sample" << tempheader.get_bytes_per_sample() << endl;
	cout << "number of samples per channel=" << tempheader.get_samples_per_channel() << endl;
	cout << "sampling rate =" << tempheader.get_sample_rate() << endl;
	return 0; //just print everything
}

Wave* Wave::stereo_to_mono()
{
	Wave* newwave;
	int* array;
	WaveHeader new_waveheader;
	new_waveheader = Wave::tempheader; //create new wave file to record mono data
	Channel** channels = nullptr;
	int length = channels[0]->get_length();
	new_waveheader.set_number_of_channels(1); // momo, only 1 channel
	new_waveheader.set_sample_rate(tempheader.get_sample_rate() / 2); //mono, half sample per channel
	array = new int[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = 0;
	} //initial array as 0;
	int value;
	for (int i = 0; i < length; i++)
	{
		value = 0;
		for (int j = 0; j < tempheader.get_number_of_channels(); j++)
		{
			value += channels[j]->get_sample(i);
		}
		array[i] = value / 2;
	}
	channels = new Channel*;
	channels[0] = new Channel(array, length); //create the new mono wave
	newwave = new Wave(new_waveheader, channels);
	delete array; //memory release
	return newwave;
}

Wave* Wave::speed_change(float speed)
{
	tempheader.set_sample_rate(speed); //just change the sample rate in header file (?)
}*/
Channel Wave::getChannel()
{
	return **channels;
}