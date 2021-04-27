#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#define FOR(i, n) for(int i=0;i<n;++i)
#define MAX_WORDS 10000

using namespace std;

struct file {
    string filename;
    int n, l, cnt_positive = 0, cnt_negative = 0;
};

int S; // number of words
int l; // lenth of each word
int n; // length of the resulting sequence

int d[MAX_WORDS][MAX_WORDS]; // distances between each of the nodes (words)
// data structure could be changed due to the fact that most distances are equal to max length

bool used[MAX_WORDS] = {false};

vector<string> words, words_used;

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

void init(file f) {

    fstream fs;
    string s;

    fs.open(f.filename.c_str());

    words.clear();
    words_used.clear();

    while (fs >> s) {
        words.push_back(s);
    }

    S = words.size();
    l = f.l;
    n = f.n;

    FOR (i, S) {
        FOR (j, S) {
            d[i][j] = dist(words[i], words[j]);
//            cout << words[i] << " " << words[j] << " " << d[i][j] << endl;
        }
    }

    for (int i = 0; i < S; ++i) {
        used[i] = false;
        cout << used[i] << " ";
    }
    cout << endl;

    cout << "Words: " << words.size() << " | Word size: " << l << endl;
}

string append_word(string temp_result, int i) {
    if (temp_result == "")
        return words[i];

    used[i] = true;
    int temp_d = dist(temp_result.substr(temp_result.size() - l, l), words[i]);


    return temp_result + words[i].substr(l - temp_d, temp_d);
}

string run(vector<string> words) {


    string result = "";

//    for (string word : words) {
//        printf("%s\n", word.c_str());
//        result += word;
//    }

    result = append_word(result, 0);
    words_used.push_back(words[0]);
    int S_used = 1;

    while (S_used < S) {
        int best_i = -1;
        int best_d = l + 1;
        FOR (i, S) {
            if (!used[i]) {
                if (result.find(words[i]) != string::npos) {
                    S_used++;
                    used[i] = true;
                } else {
                    int temp_d = dist(result, words[i]);
                    if (temp_d < best_d) {
                        best_d = temp_d;
                        best_i = i;
                    }
                }
            }
        }
        result = append_word(result, best_i);
//        cout << result << endl;
        words_used.push_back(words[best_i]);
        S_used++;
    }

    return result;
}


int main() {

    vector<file> files = {
//            {"../files/test.txt", 11, 6, 0, 0},
            {"../files/9.200-40", 209, 10, 0, 40},
//            Words: 160 | Word size: 10 | n: 209 | resulting size: 1426
//            Words: 160 | Word size: 10 | n: 209 | resulting size: 1037
    };

    for (auto file : files) {

        printf("FILE: %s\n", file.filename.c_str());

        cout << "Words: " << words.size() << " | Word size: " << l << endl;

        init(file);

        string result = run(words);

        printf("RESULT: %s\n", result.c_str());

        FOR (i, words_used.size()) {
            printf("%d: %s\n", i, words_used[i].c_str());
        }

        cout << "Words: " << S << " | Word size: " << l << " | n: " << n << " | resulting size: " << result.size() << endl;
    }
    return 0;
}
