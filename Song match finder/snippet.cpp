#include "snippet.h"

snippet::snippet(vector<int>* data, int x, string name) {
    file_name = name;
	channel_num = x;
	num_samples = data->size();
	int samples_per_5s =  44100 * 5;
	int num_snippets = num_samples / samples_per_5s;
    if(num_snippets*samples_per_5s < num_samples){
        num_snippets++;
    }
	int count = 0;

	for (int i = 0; i < num_snippets; i++) {
		vector<int> temp;
        if(i+1 < num_snippets){
            for (int j = 0; j < samples_per_5s; j++) {
                temp.push_back(data->at(count));
                count++;
            }
        } else {
            for (int j = 0; j < num_samples-(samples_per_5s*i); j++) {
                temp.push_back(data->at(count));
                count++;
            }
        }
		signature.push_back(temp);
	}
    
}

vector<vector<int>> snippet::getSignature(){
    return signature;
}

string snippet::getFile_name(){
    return file_name;
}

int snippet::getChannel_num(){
    return channel_num;
}
