//  interface.cpp
//  Wav File Editor
//
//  Created by Johannes Koechling on 2020-11-22.
//

#include "interface.h"

void Interface(string* file_address) {

    cout << "Welcome to the Plagiarism Detector!" << endl;
    cout << "Please enter the file name of the WAV file you wish to put through the system:  ";
    cin >> *file_address;
    cout << "Your file will be created under the name 'new file'.\nGoodbye \n";

}