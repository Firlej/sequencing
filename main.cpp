#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>

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
    srand((unsigned)(time(0)));

//    cout << "ELO" << endl;

    vector<Words> words = {
            {"test.txt", 11, 6, 1, 1},

            {"9.200-40", 209, 10, 0, 40},
            {"9.200-80", 209, 10, 0, 80},
            {"18.200-40", 209, 10, 0, 40},
            {"18.200-80", 209, 10, 0, 80},
            {"35.200-40", 209, 10, 0, 40},
            {"35.200-80", 209, 10, 0, 80},

            {"20.300-60", 309, 10, 0, 60},
            {"20.300-120", 309, 10, 0, 120},
            {"55.300-60", 309, 10, 0, 60},
            {"55.300-120", 309, 10, 0, 120},
            {"58.300-60", 309, 10, 0, 60},
            {"58.300-120", 309, 10, 0, 120},

            {"55.400-80", 409, 10, 0, 80},
            {"55.400-160", 409, 10, 0, 160},
            {"62.400-80", 409, 10, 0, 80},
            {"62.400-160", 409, 10, 0, 160},
            {"68.400-80", 409, 10, 0, 80},
            {"68.400-160", 409, 10, 0, 160},

            {"10.500-100", 509, 10, 0, 100},
            {"10.500-200", 509, 10, 0, 200},
            {"25.500-100", 509, 10, 0, 100},
            {"25.500-200", 509, 10, 0, 200},
            {"53.500-100", 509, 10, 0, 100},
            {"53.500-200", 509, 10, 0, 200},

            {"59.500-2", 509, 10, 0, 2},
            {"113.500-8", 509, 10, 0, 8},
            {"144.500-12", 509, 10, 0, 12},
            {"28.500-18", 509, 10, 0, 18},
            {"34.500-32", 509, 10, 0, 32},

            {"9.200+80", 209, 10, 80, 0},
            {"18.200+80", 209, 10, 80, 0},
            {"35.200+80", 209, 10, 80, 0},
            {"20.300+120", 309, 10, 120, 0},
            {"55.300+120", 309, 10, 120, 0},
            {"58.300+120", 309, 10, 120, 0},
            {"55.400+160", 409, 10, 160, 0},
            {"62.400+160", 409, 10, 160, 0},
            {"68.400+160", 409, 10, 160, 0},
            {"10.500+200", 509, 10, 200, 0},
            {"25.500+200", 509, 10, 200, 0},
            {"53.500+200", 509, 10, 200, 0},

            {"9.200+20", 209, 10, 20, 0},
            {"18.200+20", 209, 10, 20, 0},
            {"35.200+20", 209, 10, 20, 0},
            {"20.300+30", 309, 10, 30, 0},
            {"55.300+30", 309, 10, 30, 0},
            {"58.300+30", 309, 10, 30, 0},
            {"55.400+40", 409, 10, 40, 0},
            {"62.400+40", 409, 10, 40, 0},
            {"68.400+40", 409, 10, 40, 0},
            {"10.500+50", 509, 10, 50, 0},
            {"25.500+50", 509, 10, 50, 0},
            {"53.500+50", 509, 10, 50, 0},
    };

    int perfect_instance_cnt = 0; // 9 -> 19


    for (Words &words : words) {
        clock_t begin = clock();

//        cout << words.filename << endl;
        words.init();
        GA ga(&words);

//        FOR(i, 100) {
//
//            ga.next_population();
//            Individual curr_best_individual = ga.population.get_best_individual();
////            ga.population.get_best_individual().print_summary();
//
//            if (curr_best_individual.score() < best_individual.score()) {
//                best_individual = curr_best_individual;
//                best_individual.print_summary();
//            }
//
//            if (best_individual.score() <= words.n) {
//                break;
//            }
//        }

//        printf("RESULT: %s\n", best_individual.s.c_str());
//        cout << "best_individual: " << best_individual.s << endl;

//        best_individual.print_used_words();
//        best_individual.print_segments();
//        best_individual.print_negative_errors();
//        best_individual.print_positive_errors();
//        best_individual.print_summary();

//        cout << "[SHUFFLES]" << endl;
//        vector<vector<int>> segments = best_individual.get_segments();
//        int best_score = best_individual.score();
//        for (int i = 0; i < 100000000; ++i) {
//            random_shuffle(segments.begin(), segments.end());
////            print_segments(best_individual.words->words, segments, best_individual.words->l);
//            best_individual.set_word_ids(segments);
//            if (best_individual.score() < best_score) {
//                best_individual.print_summary();
//                best_score = best_individual.score();
//                if (best_score <= best_individual.words->n) {
//                    best_individual.print_summary();
//                    break;
//                }
//            }
//        }

        // print summary of results for instance
        ga.print_summary();
        if (ga.best_individual.score() <= words.n) {
//            cout << "Found valid individual!" << endl;
            perfect_instance_cnt++;
        }

    }

    cout << "Perfect instance count: " << perfect_instance_cnt << endl;

    return 0;
}
