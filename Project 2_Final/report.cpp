//
//  report.cpp
//  Wav Editing Software
//
//  Created by Johannes Koechling on 2020-12-14.
//

#include "report.hpp"
#include "fft.h"

Report::Report(){
    snippet_num = 0;
}

Report::Report(int snip_num,string f_name){
    snippet_num = snip_num;
    match_file = f_name;
}

int Report::getSnippet_num(){
    return snippet_num;
}

string Report::getMatch_file(){
    return match_file;
}

void Report::setSnippet_num(int snip_num){
    snippet_num = snip_num;
}

void Report::setMatch_file(string f_name){
    match_file = f_name;
}


Report compare(vector<int>* new_data,snippet database_song){
    
    
    int snippet_number = 0;
    bool match = false;
    
    vector<int> fft_data = get_index(*new_data);    // this line converts our vector of audio data into a vector of M values

    vector<vector<int>> snippets; // array of snippets
    
    for(int i = 0;i < database_song.getSignature().size();i++){ // this does the same thing we did to our input data to each snippet
        snippets.push_back(get_index(database_song.getSignature().at(i)));
    }
     
    
    
    vector<int> temp; // is a copy of the snippet we are comparing
    
    
    if(fft_data.size() < snippets.at(0).size()){ // if the new data is smaller than the size of a standard snippet, we do not have enough information to confirm a match
        cout << "File is too short to confirm a match." << endl;
        return Report();
    }
    
    
    for(int i = 0; i < snippets.size(); i++){ // iterates through snippets
        snippet_number = i + 1;
        match = false;
        temp = snippets.at(i);
        //int v=0; 
        
        for(int j = 0; j < fft_data.size() - temp.size(); j++)
        { // iterates through starting positions
            
            for(int z = 0; z < temp.size()-1; z++)
            { // compares the streams of data
                
                if(fft_data.size() > (z + j))
                { // this statement ensures that we don't look for data in a location beyond the scope of new_data
                    if(fft_data.at(z + j)==temp.at(z))
                    {
                        match = true;
                        //v = v + 1;
                        //cout << "Match"<<v<< endl;
                    } else 
                    {
                        //cout << "No match" << endl;
                        match = false;
                        break;
                    }                    
                }
            }
            if(match==true){
                break;
            }
        }
        
        if(match==true){
            break;
        }
    }
    
    if(match == true){
        return Report(snippet_number,database_song.getFile_name());
    } else {
        return Report();
    }
}
