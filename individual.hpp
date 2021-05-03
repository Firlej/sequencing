#pragma once

//#include <stdlib.h>
//#include <stdio.h>
#include <string>
#include <vector>
#include "utils.hpp"

using namespace std;

class Individual {
public:

    vector<int> words_ids_used;
    string s = "";

    bool used[MAX_WORDS] = {false};

    // initial individual
    Individual(int starting_index = 0) {
        words_ids_used.clear();
        int words_used_cnt = 0;

        // start with first word
        words_ids_used.push_back(starting_index);
        used[starting_index] = true;
        words_used_cnt++;

        while (words_used_cnt < S) {
            int best_i = -1;
            int best_d = l + 1;
            FOR (i, S) {
                if (!used[i]) {
                    if (find(words_ids_used.begin(), words_ids_used.end(), i) != words_ids_used.end()) {
                        words_used_cnt++;
                        used[i] = true;
                        continue;
                    } else {
                        int temp_d = dist(words[words_ids_used[words_ids_used.size() - 1]], words[i]);
                        if (temp_d < best_d) {
                            best_d = temp_d;
                            best_i = i;
                        }
                    }
                }
            }
            words_ids_used.push_back(best_i);
            used[best_i] = true;
            words_used_cnt++;
        }

        set_string();
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
        s = words[words_ids_used[0]];
        for (int i = 1; i < words_ids_used.size(); i++) {
            int temp_d = dist(words[words_ids_used[i - 1]], words[words_ids_used[i]]);
            s += words[words_ids_used[i]].substr(l - temp_d, temp_d);
        }
        return s;
    }

    // check if string contains all required words
    bool valid_string() {
        // todo modify this function for the case of positive errors present
        for (string word: words) {
            if (s.find(word) == std::string::npos) {
                printf("Invalid string!");
                return false;
            }
        }
        return true;
    }

    // fitness score. lower the better
    int score() {
        return abs(int(n - s.size()));
    }

    vector<string> get_negative_errors() {
        vector<string> negative_errors;
        for (int i = 0; i < s.size() - l + 1; i++) {
            string temp_word = s.substr(i, l);
            if (find(words.begin(), words.end(), temp_word) == words.end()) {
                negative_errors.push_back(temp_word);
            }
        }
        return negative_errors;
    }

    void print_used_words() {
        printf("USED WORDS:");
        FOR (i, words_ids_used.size()) {
            printf("%d: %s\n", i, words[words_ids_used[i]].c_str());
        }
    }

    void print_negative_errors() {
        vector<string> negative_errors = get_negative_errors();
        printf("NEGATIVE ERRORS: ");
        if (negative_errors.size() > 0) {
            for (string negative_error : negative_errors) {
                printf("%s ", negative_error.c_str());
            }
            printf("\n");
        } else {
            printf("none\n");
        }
    }

    static Individual new_individual() {
        return Individual();
    }

};
