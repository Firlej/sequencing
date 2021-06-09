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

    clock_t last_improvement;

    bool improved = false;

    // initial GA from file
    GA(Words *_words) {
        begin = clock();
        last_improvement = begin;

        words = _words;

        population = Population(_words);
        best_individual = population.get_best_individual();
//        best_individual.print_summary();
    };

    void next_population() {
        population = Population(population, best_individual);
        if (best_individual.score() > population.get_best_individual().score()) {
            best_individual = population.get_best_individual();
//            best_individual.print_summary();
            last_improvement = clock();
        }
    }

    void print_summary() {
        end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        if (last_improvement != begin) {
//            best_individual.print_summary();
        }
//        best_individual.shorten();
//        best_individual.print_summary();
        cout << "Elapsed time: " << elapsed_secs << endl;
    }

    string output() {
        end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        string s = "";

        Individual i = Individual(best_individual);
        Individual i_shortened = Individual(best_individual);
        i_shortened.shorten();

        s += words->filename + ",";
        s += to_string(words->n) + ",";
        s += to_string(i.s.size()) + ",";
        s += to_string(i_shortened.s.size()) + ",";
        s += to_string(words->S) + ",";
        s += to_string(i_shortened.words_ids_used.size()) + ",";
        s += to_string( (float) i_shortened.words_ids_used.size() / words->S ) + ",";
        s += to_string( i_shortened.words_ids_used.size() == words->S ) + ",";
        s += to_string(elapsed_secs);

        s += "\n";
        return s;
    }

    double time_from_last_improvemmnt() {
        return double(clock() - last_improvement) / CLOCKS_PER_SEC;
    }
};
