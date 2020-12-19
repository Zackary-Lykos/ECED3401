#include "snippet.h"
#include "interface.h"
using namespace std;

snippet::snippet(vector<int>* data, int x) {
    channel_num = x;// which channel is the data from
    num_samples = data->size(); // total samples
    samples_per_5s = 44100 * 5; // how many samples in one snippet 
    num_snippets = num_samples / samples_per_5s; // how many snippets will be generated !!! will lost the last part of data because the result is a [float->int]
    if (num_snippets * samples_per_5s < num_samples) { 
        num_snippets++; // include the last part of samples
    }
    int count = 0; // counter variable

    cout << "Snippet constructer initiated! Snippets included = " << num_snippets << endl;

    for (int i = 0; i < num_snippets; i++) { // loop for the number of snippet we need to create
        vector<int> temp; // creates a temp vector that "resets" after each loop
        if (i + 1 < num_snippets) { // if this is not the last loop i.e last 5 second snippet 
            for (int j = 0; j < samples_per_5s; j++) { 
                temp.push_back(data->at(count)); // copying the channel data into the temp vector of the 5 seconds segment
                count++; // increase the counter
            }
        }
        else {
            for (int j = 0; j < num_samples - (samples_per_5s * i); j++) { // if this is the last loop then number of samples in the 5 sec might not be exact
                temp.push_back(data->at(count));                           // so we dont what extra data thats not needed
                count++;
            }
        }
        signature.push_back(temp); // assign the temp vector to the signature vector the first loop signature [1][temp vector 1 or first 5 second data vector]
    }
    for (int i = 0; i < num_snippets; i++) { // the print out statement to see what how the data is organized 
        for (int j = 0; j < samples_per_5s; j++) { // if you want to stop printing the data remove or comment the code
            cout << "snippet number:" << i << "..sample number" << j << "..is.."<< signature[i][j] << endl;

        }
    }

    cout << "Snippets in signature vector = " << signature.size() << endl;
    cout << "Samples in signature vector = " << count << endl;
}
int snippet::get_num_samples() {
    return num_samples;
}
int snippet::get_num_snippets() {
    return num_snippets;
}
int snippet::get_channel_num(){
    return channel_num;
}
int snippet::get_samples_per_5s() {
    return samples_per_5s;
}
vector<vector<int>> snippet::get_signature() {
    return signature;
}