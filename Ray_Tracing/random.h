#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>
#include <random>
#include <functional>

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}
#endif