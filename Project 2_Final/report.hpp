//
//  report.hpp
//  Wav Editing Software
//
//  Created by Johannes Koechling on 2020-12-14.
//

#ifndef report_hpp
#define report_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "interface.hpp"
#include "snippet.h"
using namespace std;

class Report{
private:
    int snippet_num;
    string match_file;
public:
    int getSnippet_num();
    string getMatch_file();
    void setSnippet_num(int);
    void setMatch_file(string);
    Report(int,string);
    Report();
};

Report compare(vector<int>*,snippet);

#endif /* report_hpp */
