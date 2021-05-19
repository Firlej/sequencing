#pragma once

#include "population.hpp"

using namespace std;

class GA {
public:

    Words *words;

    Population population;

    // initial GA from file
    GA(Words *_words) {
        words = _words;

        population = Population(_words);
    };



};
