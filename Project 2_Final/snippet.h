#ifndef snippet_hpp
#define snippet_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

class snippet// This object converts a stream of audio into snippets and stores them
{
protected:
	vector<vector<int>> signature;
	int channel_num;
	int num_samples;
    string file_name;

public:
	snippet(vector<int>*, int, string);
    vector<vector<int>> getSignature();
    void setSignature(vector<vector<int>>);
    string getFile_name();
    int getChannel_num();
};

#endif

