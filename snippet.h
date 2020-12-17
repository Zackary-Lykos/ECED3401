#ifndef snippet_h
#define snippet_h

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
	int samples_per_5s;
	int num_snippets;

public:
	snippet(vector<int>*, int);
	int get_num_samples(void);
	int get_samples_per_5s(void);
	int get_num_snippets(void);
	int get_channel_num(void);
	vector<vector<int>> get_signature(void);
};

#endif
