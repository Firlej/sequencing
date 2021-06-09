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
            int best_id = -1;
            int best_d = words->l + 1;
            vector<int> best_ids;
            FOR (i, words->words.size()) {
                if (!used[i]) {
                    int temp_d = words->d[last_id()][i];
                    if (temp_d < best_d) {
                        best_ids.clear();
                        best_ids.push_back(i);
                        best_d = temp_d;
                        best_id = i;
                    } else if (temp_d == best_d) {
                        best_ids.push_back(i);
                    }
                }
            }

            // if more than one best_id check which one has better next word. very useful for positive error instances
//            int depth = 1;
            if (best_ids.size() > 1) {
                best_id = -1;
                best_d = words->l * words->S + 1;
                for (int i = 0; i < best_ids.size(); i++) {
//                    int temp_id = best_ids[i];

                    if (next_best_id(best_ids[i]) != -1) {
                        int temp_d = words->d[best_ids[i]][next_best_id(best_ids[i])];
                        if (temp_d < best_d) {
                            best_d = temp_d;
                            best_id = best_ids[i];
                        }
                    }
                }
//                for (int i = 0; i < best_ids.size(); i++) {
//                    int temp_d = words->d[best_ids[i]][next_best_id(best_ids[i])];
//                    if (temp_d != best_d) {
//                        best_ids.erase(best_ids.begin() + i);
//                        i--;
//                    }
//                }
            }
            words_ids_used.push_back(best_id);
//            cout << words->words[best_i] << " ";
            used[best_id] = true;
            // set_string();
        }
//        cout << endl;

        set_string();
//        cout << s << endl;
    };

    int last_id() {
        return words_ids_used[words_ids_used.size() - 1];
    }

    string last_word() {
        return words->words[last_id()];
    }

    int next_best_id(int id, vector<int> not_in_ids = {}) {
        int best_i = -1;
        int best_d = words->l + 1;
        FOR (i, words->words.size()) {
            if (!used[i] && i != id) {
                int temp_d = words->d[id][i];
                if (temp_d < best_d) {
                    best_d = temp_d;
                    best_i = i;
                }
            }
        }
        return best_i;
    }

    // individual from individuals from prev_pop
    Individual(vector<Individual> individuals, float fitness_sum) {

        float r = random(0.0, 1);

        if (r < 0.1) {
            // select one parent and mutate
            float p = random(0.0, fitness_sum);
            for (int i = individuals.size() - 1; i >= 0; i--) {
                fitness_sum -= individuals[i].fitness();
                if (p > fitness_sum) {
                    set(individuals[i]);
                    break;
                }
            }
            mutate();
        } else {
            // select two parents and merge
            float ar = random(0.0, fitness_sum);
            float br = random(0.0, fitness_sum);

            Individual a;
            Individual b;

            for (int i = individuals.size() - 1; i >= 0; i--) {
                fitness_sum -= individuals[i].fitness();
                if (ar > fitness_sum) {
                    a = Individual(individuals[i]);
                    break;
                }
            }
            for (int i = individuals.size() - 1; i >= 0; i--) {
                fitness_sum -= individuals[i].fitness();
                if (br > fitness_sum) {
                    b = Individual(individuals[i]);
                    break;
                }
            }

            auto sa = a.get_segments(1);
            auto sb = a.get_segments(1);
            vector<vector<int>> segments;
            while (sa.size() > 0 || sb.size() > 0) {
                if (sa.size() > 0) {
                    segments.push_back(sa[0]);
                    sa.erase(sa.begin() + 0);
                }
                if (sb.size() > 0) {
                    segments.push_back(sb[0]);
                    sb.erase(sb.begin() + 0);
                }
            }
            auto ids = segments_to_ids(segments);
            vector<int> used_ids;
            for (int i = 0; i < ids.size(); ++i) {
                if (!used[ids[i]]) {
                    used_ids.push_back(ids[i]);
                    used[ids[i]] = true;
                }
            }

//            cout << ids[max_element(ids.begin(), ids.end()) - ids.begin()] << endl;
//            cout << used_ids.size() << endl;

            words_ids_used = used_ids;
            words = a.words;

            set_string();
            valid_string();

            return;

        }
    };

    void mutate() {
        float r = random(0.0, 1.0);

        // completely new individual
        if (r < 0.05) {
            if (random(0.0, 1.0) < 0.01) {
                set(Individual(words, rand() % words->words.size()));
            }
        }

        // swap words
        if (r < 0.10) {
            while (random(0.0, 1.0) < 0.1) {
                int i1 = rand() % words_ids_used.size();
                int i2 = rand() % words_ids_used.size();
                swap(words_ids_used[i1], words_ids_used[i2]);
                float r_swap = random(0.0, 1.0);
            }
        }

        // swap segments
        if (r < 0.50) {
            auto segments = get_segments(1);
            while (random(0.0, 1.0) < 0.3) {
                int i1 = rand() % segments.size();
                int i2 = rand() % segments.size();
                swap(segments[i1], segments[i2]);
            }
            set_word_ids(segments);
        }

        // shuffle segments
        if (r < 0.70) {
            if (random(0.0, 1.0) < 0.05) {
                auto segments = get_segments(1);
                random_shuffle(segments.begin(), segments.end());
                set_word_ids(segments);
            }
        }

        set_string();
    }

    void set(Individual i) {
        // set selected individuals' properties to this one
        words = i.words;
        words_ids_used = i.words_ids_used;
        set_string();
        copy(begin(i.used), end(i.used), begin(used));
    }

    // generate a result string from words
    string set_string() {
        s = get_string(words->words, words_ids_used, words->l);
        return s;
    }

    bool valid_string() {
        // check if every word used is in string
        for (int id: words_ids_used) {
            if (s.find(words->words[id]) == std::string::npos) {
                cout << "Invalid string! " << s << " " << words->words[id] << "not present" << endl;
                return false;
            }
        }

        // check if every used id appears only once
        vector<int> used_ids_cnt(words->words.size(), 0);
        for (int id: words_ids_used) {
            used_ids_cnt[id]++;
            if (used_ids_cnt[id] > 1) {
                cout << "Invalid string! " << s << " " << words->words[id] << "appeared twice." << endl;
                return false;
            }
        }
        return true;
    }

    // fitness score. lower the better
    int score() {
        return s.size();
    }

    float fitness() {
        return (float) 100000 / score();
    }

    static Individual new_individual() {
        return Individual();
    }

    void shorten() {
        auto segments = get_segments(1);

        string s = set_string();
        int words_removed_a = 0;
        int words_removed_b = 0;

        while (s.size() > words->n) {
            vector<int> *shortest_segment = &segments[0];
            for (auto& segment: segments) {
                if (shortest_segment->size() == 0 || ( segment.size() != 0 && segment.size() < shortest_segment->size() )) {
                    shortest_segment = &segment;
                }
            }
            shortest_segment->erase(shortest_segment->end() - 1);
            words_removed_a++;
            s = get_string(words->words, segments_to_ids(segments), words->l);
        }

        s = set_string();
        auto words_ids = words_ids_used;
        while (s.size() > words->n) {
            words_ids.erase(words_ids.end() - 1);
            s = get_string(words->words, words_ids, words->l);
            words_removed_b++;
        }
//        cout << words_removed_a << " " << words_removed_b << endl;

        // check which shortening method is better and use it
        if (words_removed_a < words_removed_b) {
            set_word_ids(segments);
        } else {
            words_ids_used = words_ids;
            set_string();
        }
    }

    // SETTERS

    void set_word_ids(vector<vector<int>> segments) {
        words_ids_used = segments_to_ids(segments);
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

vector<vector<int>> Individual::get_segments(int max_dist = 1) {
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
         << " | N_ERRORS: " << get_negative_errors().size()
         << " | P_ERRORS: " << get_positive_errors().size() << endl;
}