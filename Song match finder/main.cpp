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
#include "snippet.h"
#include "report.hpp"
using namespace std;


int main()
{
    bool match = false; // This keeps track of whether a match has been found
    
    vector<Song> Database; // Database of all the songs Sleezy represents
    Database.push_back(CreateSong("Ad1.wav"));
    Database.push_back(CreateSong("classical.wav"));
    Database.push_back(CreateSong("feeling.wav"));
    Database.push_back(CreateSong("JC.wav"));
    Database.push_back(CreateSong("JC2.wav"));
    
    
    string file_name = "";
    
    Interface(&file_name); // Creating a song object for the input file
    
    Song NewSong = CreateSong(file_name);
    
    vector<int> ch1 = NewSong.GetChannel_1(); // We will compare channel 1 of the input to each channel 1 in the database
    
    vector<int> ch1_temp; // This will be the channel of the song from the database that is being compared to the input
    //ch1 is new song, ch1_temp is old song 
    for(int i = 0;i < Database.size();i++){
        Song temp = Database.at(i); //song i, like song1 ch1 -> song 2 ch2
        ch1_temp = temp.GetChannel_1();
        
        Report temp_report = compare(&ch1,snippet(&ch1_temp, 1, temp.GetFile_name())); // The generated report has all the information necessary to declare a match
        
        if(temp_report.getSnippet_num() != 0){ // If the snippet number is 0, no match was found
            cout << "Match found in snippet " << temp_report.getSnippet_num() << " of the file " << temp_report.getMatch_file() << endl;
            match = true; 
            break;
        }
    }
    
    if(match == false){
        cout << "No matches for the file " << NewSong.GetFile_name() << " found in the database." << endl;
    }
    
    cout << "Goodbye \n";
}

