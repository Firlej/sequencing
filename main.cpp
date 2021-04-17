#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "algorithm.h"

using namespace std;

vector<string> words;

void init(string filename) {

    fstream file;
    string s;

    file.open(filename.c_str());

    while (file >> s) {
        words.push_back(s);
    }
}


int main() {

    vector <string> filenames = {
            "../9.200-40",
    };

    for (string filename : filenames) {

        printf("FILE: %s\n", filename.c_str());

        init(filename);

        string result = run(words);

        printf("RESULT: %s\n", result.c_str());
    }
    return 0;
}
