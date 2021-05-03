#pragma once

#define FOR(i, n) for(int i=0;i<n;++i)
#define MAX_WORDS 10000

using namespace std;

extern vector<string> words;
extern int S, l, n;
extern int d[MAX_WORDS][MAX_WORDS];

// check if the suffix of string a is a prefix of string b
int dist(string a, string b) {
    for (int i = l; i >= 1; i--) {
        if (a.substr(l - i, i) == b.substr(0, i)) {
            return l - i;
        }
    }
    return l;
    // results could instead be the length of the resulting string created by merging the two words
}

void calc_distances() {
    FOR (i, S) {
        FOR (j, S) {
            d[i][j] = dist(words[i], words[j]);
//            cout << words[i] << " " << words[j] << " " << d[i][j] << endl;
        }
    }
}