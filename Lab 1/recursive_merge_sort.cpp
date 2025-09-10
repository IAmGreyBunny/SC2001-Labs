#include "recursive_merge_sort.hpp"
#include <cstring>
#include <functional>
using namespace std::chrono;

void mergeSortRec(int l, int r, CountableInt* pa, CountableInt* pb) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;
    mergeSortRec(l, mid, pa, pb);
    mergeSortRec(mid, r, pa, pb);
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

Result RecursiveMergeSort(int n, std::vector<CountableInt>& a) {
    std::vector<CountableInt> b(n);
    memcpy(b.data(), a.data(), n * sizeof(CountableInt));
    CountableInt* pa = a.data();
    CountableInt* pb = b.data();
    auto start = high_resolution_clock::now();
    mergeSortRec(0, n, pa, pb);
    auto end = high_resolution_clock::now();
    auto elapsedMicroseconds = duration_cast<microseconds>(end - start).count();
    return Result{ static_cast<int>(elapsedMicroseconds), comparisonCount };
}
