#pragma once
#include <vector>
#include <chrono>

extern long long comparisonCount;

struct CountableInt {
    int value{};
    bool operator<=(const CountableInt &other) const {
        ++comparisonCount;
        return value <= other.value;
    }
    bool operator>(const CountableInt &other) const {
        ++comparisonCount;
        return value > other.value;
    }
};

struct Result {
    int elapsedTime;            // microseconds
    long long comparisonCount;  // number of comparisons during the run
};

struct DataRow {
    int dataLength;
    int chunkSize = 1;
    int elapsedTime;            // microseconds
    long long comparisonCount;  // number of comparisons
};

std::vector<CountableInt> generateDataVector(int size, int seed = 12345, int min = 0, int max = 10000000);
