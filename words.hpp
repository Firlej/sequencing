#pragma once

#include "utils.hpp"

class Words {
public:

    string filename;
    int n; // length of original sequence
    int l; // length of each word
    int cnt_positive; // positive error count in instance
    int cnt_negative; // negative error count in instance

    vector<string> words;
//    int d[500][500];
    int **d;

    int S; // number of words in original sequence

    vector<vector<vector<int>>> closest_words;

    Words() {}

    Words(string _filename, int _n, int _l, int _cnt_positive, int _cnt_negative) {

//        cout << _filename << endl;

        filename = _filename;
        n = _n;
        l = _l;
        cnt_positive = _cnt_positive;
        cnt_negative = _cnt_negative;
    }

    void init() {
        fstream fs;
        string s;
        fs.open(("../files/" + filename).c_str());
        words.clear();
        while (fs >> s) {
            words.push_back(s);
        }
        fs.close();

        d = new int* [words.size()];
        FOR(i, words.size()) {
            d[i] = new int[words.size()];
            memset(d[i], false, words.size()*sizeof(int));
        }

        S = words.size() + cnt_negative - cnt_positive;

//        cout << filename << " " << n << " " << l << " " << cnt_positive << " " << cnt_negative << " " << S << endl;

        calc();
    }

    void calc() {
        FOR (i, words.size()) {
            FOR (j, words.size()) {
                d[i][j] = dist(words[i], words[j], l);
//                cout << words[i] << " " <<  words[j] << " " << d[i][j] << endl;
            }
        }
    }

    void clear() {
        words.clear();
        delete(d);
    }


};