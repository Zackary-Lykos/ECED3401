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

public:
	snippet(vector<int>*, int);
};

#endif

