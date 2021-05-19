#pragma once

//#include <stdlib.h>
//#include <stdio.h>
#include <string>
#include <vector>

#include "words.hpp"

using namespace std;

class Individual {
public:

    Words *words;

    vector<int> words_ids_used;
    string s = "";

    bool used[MAX_WORDS] = {false};
//    bool *d;

    Individual() {}

    // initial individual
    Individual(Words *_words, int starting_index = 0) {
        words = _words;

        words_ids_used.clear();
        int words_used_cnt = 0;

        // start with first word
        words_ids_used.push_back(starting_index);
        used[starting_index] = true;

        while (words_ids_used.size() < words->words.size() - words->cnt_positive) {
            int best_i = -1;
            int best_d = words->l + 1;
            FOR (i, words->words.size()) {
                if (!used[i]) {
                    // todo used to be searching in string if other words were created
                    if (false && find(words_ids_used.begin(), words_ids_used.end(), i) != words_ids_used.end()) {
                        used[i] = true;
                        continue;
                    } else {
                        int temp_d = dist(words->words[words_ids_used[words_ids_used.size() - 1]], words->words[i],
                                          words->l);
                        if (temp_d < best_d) {
                            best_d = temp_d;
                            best_i = i;
                        }
                    }
                }
            }
            words_ids_used.push_back(best_i);
//            cout << words->words[best_i] << " ";
            used[best_i] = true;
        }
//        cout << endl;

        set_string();
//        cout << s << endl;
    };

    // individual from individuals from prev_pop
    Individual(vector<Individual> individuals) {
        //
    };

    void mutate() {
        return;
    }

    // generate a result string from words
    string set_string() {
        s = get_string(words->words, words_ids_used, words->l);
        return s;
    }

    // check if string contains all required words
    bool valid_string() {
        // todo modify this function for the case of positive errors present. fixed, but needs extedning
        for (int id: words_ids_used) {
            if (s.find(words->words[id]) == std::string::npos) {
                cout << "Invalid string! " << s << " " << words->words[id] << endl;
                return false;
            }
        }
        return true;
    }

    // fitness score. lower the better
    int score() {
        return s.size();
//        return s.size() - words->n;
    }

    static Individual new_individual() {
        return Individual();
    }

    // SETTERS

    void set_word_ids(vector<vector<int>> segments) {
        words_ids_used.clear();
        for (vector<int> segment : segments) {
            words_ids_used.insert(words_ids_used.end(), segment.begin(), segment.end());
        }
        set_string();
    }

    // GETTERS

    vector<vector<int>> get_segments(int max_dist);

    vector<string> get_negative_errors();

    vector<string> get_positive_errors();

    // PRINTERS

    void print_used_words();

    void print_negative_errors();

    void print_positive_errors();

    void print_segments();

    void print_summary();

};

// GETTERS

vector<vector<int>> Individual::get_segments(int max_dist = 2) {
    vector<vector<int>> segments;
    int i = 0;
    while (i < words_ids_used.size()) {
        vector<int> segment;
        while (true) {
            segment.push_back(words_ids_used[i]);
            i++;
            if (i >= words_ids_used.size() || words->d[segment.back()][words_ids_used[i]] > max_dist) {
                break;
            }
        }
        segments.push_back(segment);
    }
    return segments;
}

vector<string> Individual::get_negative_errors() {
    vector<string> negative_errors;
    for (int i = 0; i < s.size() - words->l + 1; i++) {
        string temp_word = s.substr(i, words->l);
        if (find(words->words.begin(), words->words.end(), temp_word) == words->words.end()) {
            negative_errors.push_back(temp_word);
        }
    }
    return negative_errors;
}

vector<string> Individual::get_positive_errors() {
    vector<string> positive_errors;

    FOR(i, words->words.size()) {
        if (find(words_ids_used.begin(), words_ids_used.end(), i) == words_ids_used.end()) {
            positive_errors.push_back(words->words[i]);
        }
    }

    return positive_errors;
}

// PRINTERS

void Individual::print_segments() {
    ::print_segments(words->words, get_segments(), words->l);
}

void Individual::print_used_words() {
    printf("[USED WORDS] ");
    FOR (i, words_ids_used.size()) {
        printf("%d. %s ", i, words->words[words_ids_used[i]].c_str());
    }
    cout << endl;
}


void Individual::print_negative_errors() {
    vector<string> negative_errors = get_negative_errors();
    printf("[NEGATIVE ERRORS] ");
    if (negative_errors.size() > 0) {
        for (string negative_error : negative_errors) {
            printf("%s ", negative_error.c_str());
        }
        printf("\n");
    } else {
        printf("none\n");
    }
}

void Individual::print_positive_errors() {
    vector<string> positive_errors = get_positive_errors();
    printf("[POSITIVE ERRORS] ");
    if (positive_errors.size() > 0) {
        for (string positive_error : positive_errors) {
            printf("%s ", positive_error.c_str());
        }
        printf("\n");
    } else {
        printf("none\n");
    }
}

void Individual::print_summary() {
    cout << "File: " << words->filename
         << " | S: " << words->S
         << " | l: " << words->l
         << " | n: " << words->n
         << " | LENGTH: " << s.size()
         << " | SCORE: " << score()
         << " | N_ERRORS: " << get_negative_errors().size() << endl;
}