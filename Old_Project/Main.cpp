#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "Wave.h"
#include "FFT.h"

using namespace std;

int main(void)
{
	WaveHeader waveHeader;
	//Wave wave;
	string filename;
	cout << "type filename:";
	cin >> filename;

	Wave wave1;
	wave1.wavereader(filename);


	int input;
	// print a little menu
	cout << endl << endl << "ECED 3401 Project, choose what you want" << endl;
	cout << "1 = Add truck ..." << endl;
	cout << "2 = mono to stereo" << endl;
	cout << "3 = create loop track" << endl;
	cout << "4 = FFT" << endl;
	cout << "5 = s faster and slower" << endl;
	cout << "6 = print out the recording detail" << endl;
	cout << "7 = check history" << endl;
	cout << "8 = edit parameters" << endl;
	cout << "9 = quit" << endl << endl;
	cin >> input;

	while (1)
	{
		if (input == '1')
		{
			//does not work, don't have time to write this part
		}
		else if (input == '2')
		{
			//            wave1.stereo_to_mono();
		}
		else if (input == '3')
		{
			//does not work, don't have time to write this part
		}
		else if (input == '4')
		{
			std::complex<int> data [sizeof(long)], tmp [sizeof(long)];
			FFT fft_var;

			for (int i = 0; i<waveHeader.get_number_of_samples(); i++)
			{
				data[i] = wave1.getChannel().get_sample(i);
			}
			fft_var.fft_help(data, 6, tmp);
			// not required
		}
		else if (input == '5')
		{
			/*          cout << "speed change?";
					  cin >> speed;
					  wave1.speed_change(speed);*/
		}
		else if (input == '6')
		{
			//           wave1.print_header();
		}
		else if (input == '7')
		{
			//does not work, don't have time to write this part
		}
		else if (input == '8')
		{
			//does not work, don't have time to write this part
		}
		else if (input == '9')
		{
			break;
		}
	}

	return 0;
}