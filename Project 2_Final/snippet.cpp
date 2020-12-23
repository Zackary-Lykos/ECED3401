#include "snippet.h"

snippet::snippet(vector<int>* data, int x, string name) {// This object converts a stream of audio into snippets and stores them
    file_name = name;// name of the file
	channel_num = x;// which channel is the data from
	num_samples = data->size();// how many samples
	int samples_per_5s =  44100 * 5;
	int num_snippets = num_samples / samples_per_5s;// the number of samples in a snippet
    if(num_snippets*samples_per_5s < num_samples){// checks if the number of snippets is variable is correct
        num_snippets++;
    }
	int count = 0;// counter variable

	for (int i = 0; i < num_snippets; i++) {// loop for the number of snippet we need to create
		vector<int> temp;// creates a temp vector that "resets" after each loop
        if(i+1 < num_snippets){// if this is not the last loop i.e last 5 second snippet
            for (int j = 0; j < samples_per_5s; j++) {
                temp.push_back(data->at(count));// copying the channel data into the temp vector of the 5 seconds segment
                count++;// increase the counter
            }
        } else {
            for (int j = 0; j < num_samples-(samples_per_5s*i); j++) {// if this is the last loop then number of samples in the 5 sec might not be exact
                temp.push_back(data->at(count));// so we dont what extra data thats not needed
                count++;
            }
        }
        signature.push_back(temp);// assign the temp vector to the signature vector the first loop signature [1][temp vector 1 or first 5 second data vector]
	}
    
}

vector<vector<int>> snippet::getSignature(){
    return signature;
}

void snippet::setSignature(vector<vector<int>> new_sig){
    signature = new_sig;
}

string snippet::getFile_name(){
    return file_name;
}

int snippet::getChannel_num(){
    return channel_num;
}
