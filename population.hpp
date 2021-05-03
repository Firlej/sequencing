#pragma once

//#include <stdlib.h>
//#include <stdio.h>
#include <string>
#include <vector>
#include "individual.hpp"

using namespace std;

class Population {
public:

    int size; // population size
    vector<Individual> individuals;

    // initial population
    Population() {
        FOR (i, words.size()) {
            individuals.push_back(Individual(i));
//            printf("%d / %d\r", i, words.size());
        }
//        printf("\n");
        size = individuals.size();
    };

    // new population based on previous generation
    Population(vector<Individual> _individuals, int _size) {
        size = _size;
        individuals = _individuals;
    };

    Individual get_best_individual() {
        Individual best_individual;
        for (Individual individual : individuals) {
            // the lower the better
            if (individual.valid_string() && individual.s.size() < best_individual.s.size()) {
                best_individual = individual;
            }
        }
        return best_individual;
    }

    void print_individuals() {
        for (int i = 0; i < individuals.size(); i++) {
            printf("%d | LENGTH: %d | SCORE: %d | N_ERRORS: %d\n",
                    i,
                    individuals[i].s.size(),
                    individuals[i].score(),
                    individuals[i].get_negative_errors().size()
                    );
        }
    }

    // create a new population based on current
    Population next_population() {
        // todo
        return Population(individuals, size);
    }

};
