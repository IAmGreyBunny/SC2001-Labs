#include "types.hpp"
#include <random>

long long comparisonCount = 0;

std::vector<CountableInt> generateDataVector(int size, int seed, int min, int max) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min, max);
    std::vector<CountableInt> v(size);
    for (int i = 0; i < size; ++i) v[i].value = dist(rng);
    return v;
}
