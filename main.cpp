#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "population.hpp"

using namespace std;

struct file {
    string filename;
    int n, l, cnt_positive = 0, cnt_negative = 0;
};

int S; // number of words
int l; // length of each word
int n; // length of the resulting sequence

int d[MAX_WORDS][MAX_WORDS]; // distances between each of the nodes (words)

vector<string> words;

void run(file f) {

    // INIT

    fstream fs;
    string s;

    fs.open(f.filename.c_str());

    words.clear();

    while (fs >> s) {
        words.push_back(s);
    }

    S = words.size();
    l = f.l;
    n = f.n;

    calc_distances();

    // RUN

    Population population;

    Individual best_individual = population.get_best_individual();

//    printf("RESULT: %s\n", best_individual.s.c_str());

//    best_individual.print_used_words();
//    best_individual.print_negative_errors();

    cout << "File: " << f.filename
        << " | S: " << S
        << " | l: " << l
        << " | n: " << n
        << " | LENGTH: " << best_individual.s.size()
        << " | SCORE: " << best_individual.score()
        << " | N_ERRORS: " << best_individual.get_negative_errors().size() << endl;

//    vector<string> negative_errors = best_individual.get_negative_errors();

//    words.insert(words.end(), negative_errors.begin(), negative_errors.end());
//    S = words.size();
//    calc_distances();

//    Population population_new;
//
//    population_new.print_individuals();
//
//    Individual best_individual_new = population_new.get_best_individual();
//
//    cout << "File: " << f.filename
//         << " | S: " << S
//         << " | l: " << l
//         << " | n: " << n
//         << " | LENGTH: " << best_individual_new.s.size()
//         << " | SCORE: " << best_individual_new.score()
//         << " | N_ERRORS: " << best_individual_new.get_negative_errors().size() << endl;

//    population.print_individuals();

//    Individual individual;
//    printf("LENGTH: %d | SCORE: %d | N_ERRORS: %d\n",
//           individual.s.size(),
//           individual.score(),
//           individual.get_negative_errors().size()
//    );

}


int main() {

    vector<file> files = {
//            {"../files/test.txt", 11, 6, 0, 0},
//
            {"../files/9.200-40", 209, 10, 0, 40},
//            {"../files/9.200-80", 209, 10, 0, 80},
//            {"../files/18.200-40", 209, 10, 0, 40},
//            {"../files/18.200-80", 209, 10, 0, 80},
//            {"../files/35.200-40", 209, 10, 0, 40},
//            {"../files/35.200-80", 209, 10, 0, 80},
//
//            {"../files/20.300-60", 309, 10, 0, 60},
//            {"../files/20.300-120", 309, 10, 0, 120},
//            {"../files/55.300-60", 309, 10, 0, 60},
//            {"../files/55.300-120", 309, 10, 0, 120},
//            {"../files/58.300-60", 309, 10, 0, 60},
//            {"../files/58.300-120", 309, 10, 0, 120},
//
//            {"../files/55.400-80", 409, 10, 0, 80},
//            {"../files/55.400-160", 409, 10, 0, 160},
//            {"../files/62.400-80", 409, 10, 0, 80},
//            {"../files/62.400-160", 409, 10, 0, 160},
//            {"../files/68.400-80", 409, 10, 0, 80},
//            {"../files/68.400-160", 409, 10, 0, 160},
//
//            {"../files/10.500-100", 509, 10, 0, 100},
//            {"../files/10.500-200", 509, 10, 0, 200},
//            {"../files/25.500-100", 509, 10, 0, 100},
//            {"../files/25.500-200", 509, 10, 0, 200},
//            {"../files/53.500-100", 509, 10, 0, 100},
//            {"../files/53.500-200", 509, 10, 0, 200},

//            {"../files/9.200-40.sample", 15, 10, 0, 0},
    };

    for (auto file : files) {
        run(file);
    }
    return 0;
}
