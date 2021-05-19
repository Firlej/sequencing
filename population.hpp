#pragma once

#include "individual.hpp"

using namespace std;

class Population {
public:

    int size; // population size
    vector<Individual> individuals;

    Words *words;

    Population() {};

    Population(Words *_words) {
        words = _words;

        FOR (i, words->words.size()) {
            individuals.push_back(Individual(words, i));
        }

        size = individuals.size();
    };

    // new population based on previous generation
//    Population(vector<Individual> _individuals, int _size) {
//        size = _size;
//        individuals = _individuals;
//    };

    Individual get_best_individual() {
        Individual best_individual = individuals[0];
        for (Individual individual : individuals) {
            // the lower the better
            if ((individual.valid_string() && individual.s.size() < best_individual.s.size())) {
                best_individual = individual;
            }
        }
        return best_individual;
    }

    void print_individuals() {
        for (int i = 0; i < individuals.size(); i++) {
            printf("%d | LENGTH: %d | SCORE: %d | P_ERRORS: %d | N_ERRORS: %d\n",
                   i,
                   individuals[i].s.size(),
                   individuals[i].score(),
                   individuals[i].get_positive_errors().size(),
                   individuals[i].get_negative_errors().size()
            );
        }
    }

    // create a new population based on current
//    Population next_population() {
//        // todo
//        return Population(individuals, size);
//    }

};
