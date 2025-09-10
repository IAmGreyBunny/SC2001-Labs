#include "iterative_hybrid_sort.hpp"
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std::chrono;

inline void insertionSort(CountableInt* arr, int left, int right) {
    for (int i = left + 1; i < right; ++i) {
        CountableInt key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void mergeSortRec(int l, int r, int S, CountableInt* pa, CountableInt* pb) {
    if (r - l <= S) {
        insertionSort(pa, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    mergeSortRec(l, mid, S, pa, pb);
    mergeSortRec(mid, r, S, pa, pb);
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (pa[i] <= pa[j]) pb[k++] = pa[i++];
        else pb[k++] = pa[j++];
    }
    if (i < mid) memcpy(pb + k, pa + i, (mid - i) * sizeof(CountableInt));
    if (j < r) memcpy(pb + k, pa + j, (r - j) * sizeof(CountableInt));
    for (int idx = l; idx < r; ++idx) {
        pa[idx] = pb[idx];
    }
};

Result recursiveHybridSort(int S, int n, std::vector<CountableInt>& a) {
    std::vector<CountableInt> b(n);
    memcpy(b.data(), a.data(), n * sizeof(CountableInt));
    CountableInt* pa = a.data();
    CountableInt* pb = b.data();

    auto start = high_resolution_clock::now();

    mergeSortRec(0, n, S, pa, pb);
    auto end = high_resolution_clock::now();
    auto elapsedMicroseconds = duration_cast<microseconds>(end - start).count();
    return Result{ static_cast<int>(elapsedMicroseconds), comparisonCount };
}
