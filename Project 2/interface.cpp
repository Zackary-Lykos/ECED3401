//
//  interface.cpp
//  Wav File Editor
//
//  Created by Johannes Koechling on 2020-11-22.
//

#include "interface.hpp"

void Interface(string* file_address){
    cout << "Please enter the file name of the WAV file you wish to put through the system:  ";
    cin >> *file_address;
    cout << "Get file :" << *file_address << endl;
    
}
