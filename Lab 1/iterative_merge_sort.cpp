#include "iterative_merge_sort.hpp"
#include <cstring>
#include <algorithm>
using namespace std::chrono;

Result IterativeMergeSort(int n, std::vector<CountableInt>& a) {
    std::vector<CountableInt> b(n);
    memcpy(b.data(), a.data(), n * sizeof(CountableInt));
    CountableInt* pa = a.data();
    CountableInt* pb = b.data();
    auto start = high_resolution_clock::now();
    for (size_t width = 1; width < (size_t)n; width *= 2) {
        for (size_t l = 0; l < (size_t)n; l += 2 * width) {
            size_t r = std::min(l + 2 * width, (size_t)n);
            size_t m = std::min(l + width, (size_t)n);
            if (r == m) {
                memcpy(pb + l, pa + l, (r - l) * sizeof(CountableInt));
                continue;
            }
            size_t i = l, j = m, k = l;
            while (i < m && j < r) {
                if (pa[i] <= pa[j]) pb[k++] = pa[i++];
                else pb[k++] = pa[j++];
            }
            if (i < m) memcpy(pb + k, pa + i, (m - i) * sizeof(CountableInt));
            if (j < r) memcpy(pb + k, pa + j, (r - j) * sizeof(CountableInt));
        }
        std::swap(pa, pb);
    }
    if (pa != a.data()) memcpy(a.data(), pa, n * sizeof(CountableInt));
    auto end = high_resolution_clock::now();
    auto elapsedMicroseconds = duration_cast<microseconds>(end - start).count();
    return Result{ static_cast<int>(elapsedMicroseconds), comparisonCount };
}
