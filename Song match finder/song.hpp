//
//  song.hpp
//  Wav Editing Software
//
//  Created by Johannes Koechling on 2020-12-06.
//

#ifndef song_hpp
#define song_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

#endif /* song_hpp */


class Song{
protected:
    vector<int> channel_1;
    vector<int> channel_2;
    vector<int> channel_3;
    vector<int> channel_4;
    int num_channels;
    string file_name;
public:
    void SetNum_channels(int);
    int GetNum_channels();
    void SetFile_name(string);
    string GetFile_name();
    vector<int> GetChannel_1();
    vector<int> GetChannel_2();
    vector<int> GetChannel_3();
    vector<int> GetChannel_4();
    void SetChannel_1(vector<int>*);
    void SetChannel_2(vector<int>*);
    void SetChannel_3(vector<int>*);
    void SetChannel_4(vector<int>*);
    void CreateChannels(vector<int>*,int); // If the channels aren't already seperated, this will distribute audio data into channels automatically
    Song(vector<int>*,int,string);
};


Song CreateSong(string);
