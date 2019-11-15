#include <cstdlib>
#include "Random.h"

int Random::next(int nMax) {
    return (rand() % nMax) + 1;
}

void Random::seed(int i) {
    srand(i);
}

void Random::seed() {
    Random::seed(0);
}