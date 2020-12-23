//
//  interface.cpp
//  Wav File Editor
//
//  Created by Johannes Koechling on 2020-11-22.
//

#include "interface.hpp"

void Interface(string* file_address){// Allows the user to choose which file will be used as an input
    
    cout << "Welcome to the Song Match Detector!" << endl;
    cout << "Please enter the file name of the WAV file you wish to put through the system:  ";
    cin >> *file_address; // This input will go back to the main program and be used to create a song object
    cout << "Running " << *file_address << " through the system. We will have a result to you shortly.\n";
    
}
