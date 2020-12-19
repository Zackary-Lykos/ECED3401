//
//  main.cpp
//  Wav File Editor
//
//  Created by Johannes Koechling on 2020-11-19.
//

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "interface.hpp"
#include "song.hpp"

#include "FFT.h"
#include "snippet.h"
#include "correlation.hpp"
#include "report.hpp"
using namespace std;

namespace little_endian_io  // This code was written by the user Duthomhas on this page https://www.cplusplus.com/forum/beginner/166954/
// I tried to rewrite it for probably 8 hours but decided to try and get the functions to work first
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
//¡ü £¿£¿£¿
using namespace little_endian_io;

int main()
{
    cout << "Welcome to the Plagiarism Detector!" << endl;
    cout << "First, enter previously released song name (5 internal)" << endl;
    vector<int> ch1;
    vector<int> ch2;
    vector<int> ch3;
    vector<int> ch4;
    string file_name = "";
    int index_array[10][1024]; /* hard code, when set variables it always show error : cannot be used as an constant*/
    //set array into matrix format.[10] is num_file*num_channel, [1024]means 1024 index numbers in one channel
    int internal_to_external_mode = 0;
    while (internal_to_external_mode == 0)
    {
        Interface(&file_name);//input file name
        Song NewSong = CreateSong(file_name);
        ch1 = NewSong.GetChannel_1();
        ch2 = NewSong.GetChannel_2();
        ch3 = NewSong.GetChannel_3();
        ch4 = NewSong.GetChannel_4();//seperate channel 1,2,3,4 for old released music file, store each channel in vector chx

        int channels = NewSong.GetNum_channels();
        //¡ý do fft to channel 1,2,3,4, fft doesn't work¡ý//
        cout << "FFT test";
        std::complex<int> ch1data[sizeof(long)], tmp1[sizeof(long)];
        std::complex<int> ch2data[sizeof(long)], tmp2[sizeof(long)];
        std::complex<int> ch3data[sizeof(long)], tmp3[sizeof(long)];
        std::complex<int> ch4data[sizeof(long)], tmp4[sizeof(long)];
        int N = 1024; //seperate each channel into 1024 segment, select 1 index number for each segment.
        FFT fft_war; 
        vector<int> index_array; //
        if (channels == 1)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                fft_war.fft_help(ch1data, N, tmp1);

            }
        }
        if (channels == 2)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                ch2data[i] = ch2[i];
                fft_war.fft_help(ch1data, N, tmp1);
                fft_war.fft_help(ch2data, N, tmp2);
            }
        }
        if (channels == 3)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                ch2data[i] = ch2[i];
                ch3data[i] = ch3[i];
                fft_war.fft_help(ch1data, N, tmp1);
                fft_war.fft_help(ch2data, N, tmp2);
                fft_war.fft_help(ch3data, N, tmp3);
            }
        }
        if (channels == 4)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                ch2data[i] = ch2[i];
                ch3data[i] = ch3[i];
                ch4data[i] = ch4[i];
                fft_war.fft_help(ch1data, N, tmp1);
                fft_war.fft_help(ch2data, N, tmp2);
                fft_war.fft_help(ch3data, N, tmp3);
                fft_war.fft_help(ch4data, N, tmp4);
            }
        }
        
        //Finish channel seperation, FFT should be done at there. chxdata or an array should export as index array.


        cout << "file:"<< file_name << " "<<"done" << endl;
        cout << "0 = previous released music,1 = new released music"<<endl;
        cin >> internal_to_external_mode;
        if (internal_to_external_mode == 1)
        {
            break;
        }
    }
//currently fft doesn't work
/*expected output (index array):
    CH[File order][Channel]=[1024 index] 
    CH[ ][ ]=[1,2,3,4,5,6,7,8,9...1024 //file 1 channel 1 index array
              1,2,3,4,5,6,7,8,9...1024 //file 1 chaneel 2 index array (can add channel 3, 4, line by line compare)
              1,2,3,4,5,6,7,8,9...1024 //file 2 channel 1 index array
              1,2,3,4,5,6,7,8,9...1024 //file 2 channel 2 index array
              1,2,3,4,5,6,7,8,9...1024 //file 3 channel 1 index array
              1,2,3,4,5,6,7,8,9...1024 //file 3 channel 2 index array
              1,2,3,4,5,6,7,8,9...1024 //file 4 channel 1 index array
              1,2,3,4,5,6,7,8,9...1024 //file 4 channel 2 index array             
              1,2,3,4,5,6,7,8,9...1024 //file 5 channel 1 index array  
              1,2,3,4,5,6,7,8,9...1024]//file 5 channel 2 index array  
              !index matirx should stored in system. this part is not tested !
              
*/
//Switch to input the external file.
    vector<vector<int>> snippeted_ch1;
    vector<vector<int>> snippeted_ch2;
    vector<vector<int>> snippeted_ch3;
    vector<vector<int>> snippeted_ch4;
    cout << "go to new released file" << endl;
    while (internal_to_external_mode == 1)
    {
        Interface(&file_name);//set filemame = file_name
        //snippet Part, wait for output format

        Song NewSong = CreateSong(file_name);
        ch1 = NewSong.GetChannel_1();//full length channel data
        ch2 = NewSong.GetChannel_2();
        ch3 = NewSong.GetChannel_3();
        ch4 = NewSong.GetChannel_4();

        int channels = NewSong.GetNum_channels();
        if (channels == 1)
        {
            snippet ch1_snippet(&ch1, 1); // calls the snippet constructor -> get channel 1 data, set channel 1
            snippeted_ch1 = ch1_snippet.get_signature();//move result to the outside for other use.
        }
        else if (channels == 2)
        {
            snippet ch1_snippet(&ch1, 1);
            snippeted_ch1 = ch1_snippet.get_signature();
            snippet ch2_snippet(&ch2, 2);
            snippeted_ch2 = ch2_snippet.get_signature();
        }
        else if (channels == 3)
        {
            snippet ch1_snippet(&ch1, 1);
            snippeted_ch1 = ch1_snippet.get_signature();
            snippet ch2_snippet(&ch2, 2);
            snippeted_ch2 = ch2_snippet.get_signature();
            snippet ch3_snippet(&ch3, 3);
            snippeted_ch3 = ch3_snippet.get_signature();
        }
        else if (channels == 4)
        {
            snippet ch1_snippet(&ch1, 1);
            snippeted_ch1 = ch1_snippet.get_signature();
            snippet ch2_snippet(&ch2, 2);
            snippeted_ch2 = ch2_snippet.get_signature();
            snippet ch3_snippet(&ch3, 3);
            snippeted_ch3 = ch3_snippet.get_signature();
            snippet ch4_snippet(&ch4, 4);
            snippeted_ch4 = ch4_snippet.get_signature();
        }
        //snippet format for one channel: signature[0] = [1, 2, 3, 4, 5, 6, 7....channel 1 data in 0~5 seconds, 220500 data for feeling.wav]
                        //signature[1] = [1, 2, 3, 4, 5, 6, 7....channel 1 data in 5~10 seconds]
                        //....
                        //signature[6] = [1, 2, 3, 4, 5, 6, 7....channel 1 data in last few seconds,< 220500 data]


        cout << "FFT test2";
        std::complex<int> ch1data[sizeof(long)], tmp1[sizeof(long)];//Éè¶¨ÒôÆµ2µÄ1234
        std::complex<int> ch2data[sizeof(long)], tmp2[sizeof(long)];
        std::complex<int> ch3data[sizeof(long)], tmp3[sizeof(long)];
        std::complex<int> ch4data[sizeof(long)], tmp4[sizeof(long)];
        int N = 1024;
        FFT fft_war;
        if (channels == 1)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                fft_war.fft_help(ch1data, N, tmp1);
            }
        }
        if (channels == 2)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                ch2data[i] = ch2[i];
                fft_war.fft_help(ch1data, N, tmp1);
                fft_war.fft_help(ch2data, N, tmp2);
            }
        }
        if (channels == 3)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                ch2data[i] = ch2[i];
                ch3data[i] = ch3[i];
                fft_war.fft_help(ch1data, N, tmp1);
                fft_war.fft_help(ch2data, N, tmp2);
                fft_war.fft_help(ch3data, N, tmp3);
            }
        }
        if (channels == 4)
        {
            for (int i = 0; i < ch1.size(); i++)
            {
                ch1data[i] = ch1[i];
                ch2data[i] = ch2[i];
                ch3data[i] = ch3[i];
                ch4data[i] = ch4[i];
                fft_war.fft_help(ch1data, N, tmp1);
                fft_war.fft_help(ch2data, N, tmp2);
                fft_war.fft_help(ch3data, N, tmp3);
                fft_war.fft_help(ch4data, N, tmp4);
            }
        }
    }
}

