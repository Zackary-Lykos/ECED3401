//
//  report.cpp
//  Wav Editing Software
//
//  Created by Johannes Koechling on 2020-12-14.
//

#include "report.hpp"

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

/*
int getSnippet_num();
string getMatch_file();
void setSnippet_num(int);
void setMatch_file(string);
*/

Report compare(vector<int>* new_data,snippet database_song){
    
    
    int snippet_number = 0;
    bool match = false;

    vector<vector<int>> snippets = database_song.getSignature(); // array of snippets
    vector<int> temp; // is a copy of the snippet we are comparing
    
    
    if(new_data->size() < snippets.at(0).size()){ // if the new data is smaller than a standard snippet, we do not have enough information to confirm a match
        cout << "File is too short to confirm a match." << endl;
        return Report();
    }
    
    
    for(int i = 0; i < snippets.size(); i++){ // iterates through snippets
        snippet_number = i + 1;
        match = false;
        temp = snippets.at(i);
        
        for(int j = 0; j < new_data->size() - temp.size(); j++){ // iterates through starting positions
            
            for(int z = 0; z < temp.size(); z++){ // compares the streams of data
                
                if(new_data->size() > (z + j)){ // this statement ensures that we don't look for data in a location beyond the scope of new_data
                    if(new_data->at(z + j)==temp.at(z)){
                        match = true;
                        //cout << "Match" << endl;
                    } else {
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
    
    if(match){
        //cout << "Match found in snippet " << snippet_number << " of channel " << database_song.getChannel_num() << " of the file " << database_song.getFile_name() << endl;
        return Report(snippet_number,database_song.getFile_name());
    } else {
        //cout << "No matches found in channel " << database_song.getChannel_num() << " of the file " << database_song.getFile_name() << endl;
        return Report();
    }
}
