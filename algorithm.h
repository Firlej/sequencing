#pragma once

#include <string>
#include <vector>

#define FOR(i, n) for(int i=0;i<n;++i)

using namespace std;

string run(vector<string> words) {

    string result = "";

    for (string word : words) {
        printf("%s\n", word.c_str());
        result += word;
    }

    return result;
}
