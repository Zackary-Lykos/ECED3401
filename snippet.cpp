#include "snippet.h"

snippet::snippet(vector<int>* data, int x) {
	channel_num = x;
	num_samples = data->size();
	int samples_per_5s =  44100 * 5;
	int num_snippets = num_samples / samples_per_5s;
	int count = 0;

	for (int i = 0; i < num_snippets; i++) {
		vector<int> temp;
		for (int j = 0; j < samples_per_5s; i++) {
			temp.push_back(data->at(count));
			count++;
		}
		signature.push_back(temp);
	}
}