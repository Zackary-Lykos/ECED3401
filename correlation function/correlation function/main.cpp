//
//  main.cpp
//  correlation function
//
//  Created by Johannes Koechling on 2020-12-17.
//

#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "report.hpp"
#include "correlation.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    vector<vector<int>> set_of_snippets;
    vector<int> temp;
    vector<int> info_to_match;
    
    for(int i = 0;i < 3;i++){ // Fills set_of_snippets, snippet 1 is 1-5, snippet 2 is 6-10, snippet 3 is 11-15
        for(int j = 0;j < 5;j++){
            temp.push_back((i*5)+j+1);
        }
        set_of_snippets.push_back(temp);
        temp.clear();
    }
    
    info_to_match.push_back(7);
    info_to_match.push_back(5);
    info_to_match.push_back(6);
    info_to_match.push_back(7);
    info_to_match.push_back(8);
    info_to_match.push_back(9);
    info_to_match.push_back(10);
    info_to_match.push_back(8);
    info_to_match.push_back(9);
    
    Report result = correlation(&info_to_match,&set_of_snippets,"bootylicious");
    
    std::cout << result.getMatch_file();
    return 0;
}
