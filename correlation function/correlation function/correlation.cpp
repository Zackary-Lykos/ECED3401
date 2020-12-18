//
//  correlation.cpp
//  correlation function
//
//  Created by Johannes Koechling on 2020-12-17.
//

#include "correlation.hpp"

Report correlation(vector<int>* new_data, vector<vector<int>>* snippets, string f_name){
    
    int snippet_number;
    bool match;
    
    vector<int> temp; // is a copy of the snippet we are comparing
    
    for(int i = 0; i < snippets->size(); i++){ // iterates through snippets
        snippet_number = i + 1;
        match = false;
        temp = snippets->at(i);
        
        for(int j = 0; j < new_data->size() - temp.size(); j++){ // iterates through starting positions
            
            for(int z = 0; z < temp.size(); z++){ // compares the streams of data
                
                if(new_data->at(z + j)==temp.at(z)){
                    match = true;
                    cout << "Match" << endl;
                } else {
                    cout << "No match" << endl;
                    match = false;
                    break;
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
    
    
    if(match==true){
        cout << "Match found in snippet " << snippet_number << " of the file " << f_name << endl;
        return Report(snippet_number,f_name);
    } else {
        cout << "No matches found in the file " << f_name << endl;
        return Report();
    }

}
