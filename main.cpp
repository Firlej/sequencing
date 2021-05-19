#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "words.hpp"
#include "ga.hpp"

using namespace std;

void run() {

    // RUN

//    Population population;


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

int r(int i) { return std::rand() % i; }


int main() {

    vector<Words> words = {
//            {"../files/test.txt", 11, 6, 1, 1},

//            {"../files/9.200-40", 209, 10, 0, 40},
//            {"../files/9.200-80", 209, 10, 0, 80},
            {"../files/18.200-40", 209, 10, 0, 40},
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
//
//            {"../files/9.200-40.sample", 15, 10, 0, 0},
    };

    for (Words &words : words) {
        GA ga(&words);

        ga.population.print_individuals();

        Individual best_individual = ga.population.get_best_individual();

//        printf("RESULT: %s\n", best_individual.s.c_str());
        cout << "best_individual: " << best_individual.s << endl;

//        best_individual.print_used_words();
        best_individual.print_segments();
        best_individual.print_negative_errors();
        best_individual.print_positive_errors();
        best_individual.print_summary();

        cout << "[SHUFFLES]" << endl;
        vector<vector<int>> segments = best_individual.get_segments();
        int best_score = best_individual.score();
        for (int i = 0; i < 100000000; ++i) {
            random_shuffle(segments.begin(), segments.end(), r);
//            print_segments(best_individual.words->words, segments, best_individual.words->l);
            best_individual.set_word_ids(segments);
            if (best_individual.score() < best_score) {
                best_individual.print_summary();
                best_score = best_individual.score();
                if (best_score <= best_individual.words->n) {
                    best_individual.print_summary();
                    break;
                }
            }
        }
    }

    return 0;
}
