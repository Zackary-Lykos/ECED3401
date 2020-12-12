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
using namespace std;

/*
    There is a bit of noise at the end of each file, I don't know why, but it might have something to do with some data that happens after the audio data (even though in theory that doesn't fit the wav format) so I apologize for the noise at the end of each set of samples.
 */




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
using namespace little_endian_io;



int main()
{
    string file_name = "";
    

    Interface(&file_name);
    
    Song NewSong = CreateSong(file_name);
    
    vector<int> ch1 = NewSong.GetChannel_1();
    vector<int> ch2 = NewSong.GetChannel_2();
    vector<int> ch3 = NewSong.GetChannel_3();
    vector<int> ch4 = NewSong.GetChannel_4();
    int channels = NewSong.GetNum_channels();
    //****��Read Input File�� seperate into channel��****//

    //*****************��FFT transform��*****************//
    cout << "FFT test";

    std::complex<int> ch1data[sizeof(long)], tmp[sizeof(long)];//2
    std::complex<int> ch2data[sizeof(long)], tmp[sizeof(long)];
    std::complex<int> ch3data[sizeof(long)], tmp[sizeof(long)];
    std::complex<int> ch4data[sizeof(long)], tmp[sizeof(long)];
    int N = 1024;
    FFT fft_war;
    if (channels == 1)
    {
        for (int i = 0; i < ch1.size(); i++)
        {
            ch1data[i] = ch1[i];
            fft_war.fft_help(ch1data, N, tmp);
        }
    }
    if (channels == 2)
    {
        for (int i = 0; i < ch1.size(); i++)
        {
            ch1data[i] = ch1[i];
            ch2data[i] = ch2[i];
            fft_war.fft_help(ch1data, N, tmp);
            fft_war.fft_help(ch2data, N, tmp);
        }
    }
    if (channels == 3)
    {
        for (int i = 0; i < ch1.size(); i++)
        {
            ch1data[i] = ch1[i];
            ch2data[i] = ch2[i];
            ch3data[i] = ch3[i];
            fft_war.fft_help(ch1data, N, tmp);
            fft_war.fft_help(ch2data, N, tmp);
            fft_war.fft_help(ch3data, N, tmp);
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
            fft_war.fft_help(ch1data, N, tmp);
            fft_war.fft_help(ch2data, N, tmp);
            fft_war.fft_help(ch3data, N, tmp);
            fft_war.fft_help(ch4data, N, tmp);
        }
    }//ch1,2,3,4data are now in frequency domain, next step: find maximum in each file
    //*****************��FFT transform��*****************//

    //*************��Find 1024 Index value��*************//

    
    /*for (int i = 0; i < waveHeader.get_number_of_samples(); i++)
    {
        data[i] = wave1.getChannel().get_sample(i);
    }
    fft_var.fft_help(data, 6, tmp);*/
    
  /*ofstream f( "new file.wav", ios::binary | ios::out); // Here's where I apply the function from the code I found online, linked above.
    f << "RIFF----WAVEfmt ";
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    write_word( f,      channels, 2 );  // number of channels
    write_word( f,  44100, 4 );  // samples per second (Hz)
    write_word( f, 88200*channels, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word( f,     16, 2 );  // number of bits per sample (use a multiple of 8)
   
    f << "data----";  // (chunk size to be filled in later)
    long int chunk2_pos = f.tellp();
    
    
    int sample_count = ch1.size() + ch2.size() + ch3.size() + ch4.size();
    
    int value;

    for (int n = 0; n < ch1.size(); n++)  //  Writes data into new wav file
    {
        
        value = ch1.at(n);
        f.put(value>>8 & 0xff);
        f.put(value & 0xff);
        
        if(channels == 2){
            value = ch2.at(n);
            f.put(value>>8 & 0xff);
            f.put(value & 0xff);
        }
        else if(channels == 3){
            value = ch2.at(n);
            f.put(value>>8 & 0xff);
            f.put(value & 0xff);
            value = ch3.at(n);
            f.put(value>>8 & 0xff);
            f.put(value & 0xff);
        }
        else if(channels == 4){
            value = ch2.at(n);
            f.put(value>>8 & 0xff);
            f.put(value & 0xff);
            value = ch3.at(n);
            f.put(value>>8 & 0xff);
            f.put(value & 0xff);
            value = ch4.at(n);
            f.put(value>>8 & 0xff);
            f.put(value & 0xff);
        }
        
    }
        
    
    
    f.seekp(0,ios::end);
    int f_size = f.tellp();
    f.seekp(4,ios::beg);
    write_word(f, f_size - 8, 4); // Chunk size
    
    f.seekp(chunk2_pos,ios::beg);
    write_word(f, channels*sample_count*2/8, 4); // Subchunk 2 size
    
    //inFile.close();
    f.close();
    */
}

