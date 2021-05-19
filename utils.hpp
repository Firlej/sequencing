#pragma once

#include <string>

#define FOR(i, n) for(int i=0;i<n;++i)
#define MAX_WORDS 1001

using namespace std;

// check if the suffix of string a is a prefix of string b
int dist(string a, string b, int l) {
    for (int i = l; i >= 1; i--) {
        if (a.substr(l - i, i) == b.substr(0, i)) {
            return l - i;
        }
    }
    return l;
    // results could instead be the length of the resulting string created by merging the two words
}

// generate a result string from words
string get_string(vector<string> words, vector<int> word_ids, int l) {
    string s = words[word_ids[0]];
    for (int i = 1; i < word_ids.size(); i++) {
        int d = dist(words[word_ids[i - 1]], words[word_ids[i]], l);
        s += words[word_ids[i]].substr(l - d, d);
    }
    return s;
}

// generate a result string from words
string get_string(vector<string> words, int l) {
    string s = words[0];
    for (int i = 1; i < words.size(); i++) {
        int d = dist(words[i - 1], words[i], l);
        s += words[i].substr(l - d, d);
    }
    return s;
}

void print_segments(vector<string> words, vector<vector<int>> segments, int l) {
    cout << "[SEGMENTS]" << endl;
    for (vector<int> segment : segments) {
        cout << get_string(words, segment, l) << endl;
    }
}