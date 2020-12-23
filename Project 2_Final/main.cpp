//
//  main.cpp
//  Wav File Editor
//
//  Created by:
//  Johannes Koechling (B00777255)
//  Matthew Cockburn (B00788268)
//  Zhang Yiming (B00810985)
//  Angelo Diggs (B00723134)
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
    vector<int> ch2 = NewSong.GetChannel_2();
    vector<int> ch3 = NewSong.GetChannel_3();
    vector<int> ch4 = NewSong.GetChannel_4();
    
    vector<int> ch1_temp; // This will be the channel of the song from the database that is being compared to the input
    vector<int> ch2_temp;
    vector<int> ch3_temp;
    vector<int> ch4_temp;
    
    for(int i = 0;i < Database.size();i++){ // // Iterates through songs in the database
        Song temp = Database.at(i);
        ch1_temp = temp.GetChannel_1();
        ch2_temp = temp.GetChannel_2();
        ch3_temp = temp.GetChannel_3();
        ch4_temp = temp.GetChannel_4();
        
        Report temp_report = compare(&ch1,snippet(&ch1_temp, 1, temp.GetFile_name())); // The generated report has all the information necessary to declare a match, all of the FFT operations happen in the compare function
        
        if(temp_report.getSnippet_num() != 0){ // If the snippet number is 0, no match was found
            cout << "Match found in snippet " << temp_report.getSnippet_num() << " of the file " << temp_report.getMatch_file() << endl;
            match = true;
            break;
        }
        
        Report temp_report2 = compare(&ch2,snippet(&ch2_temp, 2, temp.GetFile_name())); // The generated report has all the information necessary to declare a match, all of the FFT operations happen in the compare function
        
        if(temp_report2.getSnippet_num() != 0){ // If the snippet number is 0, no match was found
            cout << "Match found in snippet " << temp_report2.getSnippet_num() << " of the file " << temp_report2.getMatch_file() << endl;
            match = true;
            break;
        }
        /* // if the wav has < 2 channels, this part will cause error.
        Report temp_report3 = compare(&ch3,snippet(&ch3_temp, 3, temp.GetFile_name())); // The generated report has all the information necessary to declare a match, all of the FFT operations happen in the compare function
        
        if(temp_report.getSnippet_num() != 0){ // If the snippet number is 0, no match was found
            cout << "Match found in snippet " << temp_report3.getSnippet_num() << " of the file " << temp_report3.getMatch_file() << endl;
            match = true;
            break;
        }
        
        Report temp_report4 = compare(&ch4,snippet(&ch4_temp, 4, temp.GetFile_name())); // The generated report has all the information necessary to declare a match, all of the FFT operations happen in the compare function
        
        if(temp_report4.getSnippet_num() != 0){ // If the snippet number is 0, no match was found
            cout << "Match found in snippet " << temp_report4.getSnippet_num() << " of the file " << temp_report4.getMatch_file() << endl;
            match = true;
            break;
        }*/
    }
    
    if(match == false){// Informs the user if no match is found
        cout << "No matches for the file " << NewSong.GetFile_name() << " found in the database." << endl;
    }
    
    cout << "Goodbye \n";
}

