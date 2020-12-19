#ifndef snippet_hpp
#define snippet_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

class snippet
{
protected:
	vector<vector<int>> signature;
	int channel_num;
	int num_samples;
    string file_name;

public:
	snippet(vector<int>*, int, string);
    vector<vector<int>> getSignature();
    string getFile_name();
    int getChannel_num();
};

#endif

