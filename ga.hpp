#pragma once

#include "population.hpp"

using namespace std;

class GA {
public:

    Words *words;

    Population population;
    Individual best_individual;

    clock_t begin;
    clock_t end;
    double elapsed_secs;

    // initial GA from file
    GA(Words *_words) {
        begin = clock();
        words = _words;

        population = Population(_words);
        best_individual = population.get_best_individual();
    };

    void next_population() {
        population = Population(population, best_individual);
        if (best_individual.score() > population.get_best_individual().score()) {
            best_individual = population.get_best_individual();
        }
    }

    void print_summary() {
        end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        best_individual.print_summary();
//        cout << "Elapsed time: " << elapsed_secs << endl;
    }
};
