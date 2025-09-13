#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "types.hpp"
#include "iterative_hybrid_sort.hpp"
#include "recursive_hybrid_sort.hpp"
#include "iterative_merge_sort.hpp"
#include "recursive_merge_sort.hpp"

using namespace std;

vector<DataRow> recursiveHybridSortResultTable; 
vector<DataRow> iterativeHybridSortResultTable;
vector<DataRow> recursiveMergeSortResultTable;
vector<DataRow> iterativeMergeSortResultTable;

int main() {

    //Different parameter controlling the benchmarking
    const int LOOP_COUNT = 10;          // controls how many times the code is run for one input. more means more accurate but takes longer to execute.
    const int CHUNK_SIZE_LIMIT = 1024;  // chunk size to test to

    for (int dataSize = 1000; dataSize < 20000000; dataSize *= 2) {

        // This generate the data
        vector<CountableInt> dataVector = generateDataVector(dataSize);

        // make a copy for each sort to ensure same input. Original will be passed to sorts for sanity checks.
        vector<CountableInt> dataVectorCopy = dataVector; 

        for (int chunkSize = 2; chunkSize <= CHUNK_SIZE_LIMIT; chunkSize *= 2) {
            int averageTime = 0;
            for (int i = 0; i < LOOP_COUNT; i++) {
                dataVector = dataVectorCopy; 
                comparisonCount = 0;
                Result res = recursiveHybridSort(chunkSize, dataSize, dataVector);
                assert(std::is_sorted(dataVector.begin(), dataVector.end(), [](const CountableInt& a, const CountableInt& b) { return a.value < b.value; }));
                averageTime += res.elapsedTime;
            }
            averageTime /= LOOP_COUNT;
            recursiveHybridSortResultTable.push_back({ dataSize, chunkSize, averageTime, comparisonCount });
            cout << "Finished: Recursive Hybrid Sort, dataSize=" << dataSize << ", chunkSize=" << chunkSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;
        }

        for (int chunkSize = 2; chunkSize <= CHUNK_SIZE_LIMIT; chunkSize *= 2) {
            int averageTime = 0;
            for (int i = 0; i < LOOP_COUNT; i++) {
                dataVector = dataVectorCopy;
                comparisonCount = 0;
                Result res = iterativeHybridSort(chunkSize, dataSize, dataVector);
                assert(std::is_sorted(dataVector.begin(), dataVector.end(), [](const CountableInt& a, const CountableInt& b) { return a.value < b.value; }));
                averageTime += res.elapsedTime;
            }
            averageTime /= LOOP_COUNT;
            iterativeHybridSortResultTable.push_back({ dataSize, chunkSize, averageTime, comparisonCount });
            cout << "Finished: Iterative Hybrid Sort, dataSize=" << dataSize << ", chunkSize=" << chunkSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;
        }

        int averageTime = 0;
        for (int i = 0; i < LOOP_COUNT; i++) {
            dataVector = dataVectorCopy;
            comparisonCount = 0;
            Result res = RecursiveMergeSort(dataSize, dataVector);
            averageTime += res.elapsedTime;
        }
        averageTime /= LOOP_COUNT;
        recursiveMergeSortResultTable.push_back({ dataSize, 1, averageTime, comparisonCount });
        cout << "Finished: Recursive Merge Sort, dataSize=" << dataSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;

        averageTime = 0;
        for (int i = 0; i < LOOP_COUNT; i++) {
            dataVector = dataVectorCopy;
            comparisonCount = 0;
            Result res = IterativeMergeSort(dataSize, dataVector);
            averageTime += res.elapsedTime;
        }
        averageTime /= LOOP_COUNT;
        iterativeMergeSortResultTable.push_back({ dataSize, 1, averageTime, comparisonCount });
        cout << "Finished: Iterative Merge Sort, dataSize=" << dataSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;
    }

    // Run benchmark one more time to make sure 10 million is one of the datapoint
    {
        int dataSize = 10000000;
        // This generate the data
        vector<CountableInt> dataVector = generateDataVector(dataSize);

        // make a copy for each sort to ensure same input. Original will be passed to sorts for sanity checks.
        vector<CountableInt> dataVectorCopy = dataVector;

        for (int chunkSize = 2; chunkSize <= CHUNK_SIZE_LIMIT; chunkSize *= 2) {
            int averageTime = 0;
            for (int i = 0; i < LOOP_COUNT; i++) {
                dataVector = dataVectorCopy;
                comparisonCount = 0;
                Result res = recursiveHybridSort(chunkSize, dataSize, dataVector);
                assert(std::is_sorted(dataVector.begin(), dataVector.end(), [](const CountableInt& a, const CountableInt& b) { return a.value < b.value; }));
                averageTime += res.elapsedTime;
            }
            averageTime /= LOOP_COUNT;
            recursiveHybridSortResultTable.push_back({ dataSize, chunkSize, averageTime, comparisonCount });
            cout << "Finished: Recursive Hybrid Sort, dataSize=" << dataSize << ", chunkSize=" << chunkSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;
        }

        for (int chunkSize = 2; chunkSize <= CHUNK_SIZE_LIMIT; chunkSize *= 2) {
            int averageTime = 0;
            for (int i = 0; i < LOOP_COUNT; i++) {
                dataVector = dataVectorCopy;
                comparisonCount = 0;
                Result res = iterativeHybridSort(chunkSize, dataSize, dataVector);
                assert(std::is_sorted(dataVector.begin(), dataVector.end(), [](const CountableInt& a, const CountableInt& b) { return a.value < b.value; }));
                averageTime += res.elapsedTime;
            }
            averageTime /= LOOP_COUNT;
            iterativeHybridSortResultTable.push_back({ dataSize, chunkSize, averageTime, comparisonCount });
            cout << "Finished: Iterative Hybrid Sort, dataSize=" << dataSize << ", chunkSize=" << chunkSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;
        }

        int averageTime = 0;
        for (int i = 0; i < LOOP_COUNT; i++) {
            dataVector = dataVectorCopy;
            comparisonCount = 0;
            Result res = RecursiveMergeSort(dataSize, dataVector);
            averageTime += res.elapsedTime;
        }
        averageTime /= LOOP_COUNT;
        recursiveMergeSortResultTable.push_back({ dataSize, 1, averageTime, comparisonCount });
        cout << "Finished: Recursive Merge Sort, dataSize=" << dataSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;

        averageTime = 0;
        for (int i = 0; i < LOOP_COUNT; i++) {
            dataVector = dataVectorCopy;
            comparisonCount = 0;
            Result res = IterativeMergeSort(dataSize, dataVector);
            averageTime += res.elapsedTime;
        }
        averageTime /= LOOP_COUNT;
        iterativeMergeSortResultTable.push_back({ dataSize, 1, averageTime, comparisonCount });
        cout << "Finished: Iterative Merge Sort, dataSize=" << dataSize << ", time=" << averageTime << " microseconds, comparisonCount=" << comparisonCount << endl;
    }




    // Writing Results to CSV
    ofstream outRecursive("recursiveHybridSortResult.csv");
    outRecursive << "DataLength,ChunkSize,Time(microseconds),ComparisonCount\n";
    for (auto& row : recursiveHybridSortResultTable) {
        outRecursive << row.dataLength << "," << row.chunkSize << "," << row.elapsedTime << "," << row.comparisonCount << "\n";
    }
    outRecursive.close();

    ofstream outIterative("iterativeHybridSortResult.csv");
    outIterative << "DataLength,ChunkSize,Time(microseconds),ComparisonCount\n";
    for (auto& row : iterativeHybridSortResultTable) {
        outIterative << row.dataLength << "," << row.chunkSize << "," << row.elapsedTime << "," << row.comparisonCount << "\n";
    }
    outIterative.close();

    outRecursive.open("recursiveMergeSortResult.csv");
    outRecursive << "DataLength,ChunkSize,Time(microseconds),ComparisonCount\n";
    for (auto& row : recursiveMergeSortResultTable) {
        outRecursive << row.dataLength << "," << row.chunkSize << "," << row.elapsedTime << "," << row.comparisonCount << "\n";
    }
    outRecursive.close();

    outIterative.open("iterativeMergeSortResult.csv");
    outIterative << "DataLength,ChunkSize,Time(microseconds),ComparisonCount\n";
    for (auto& row : iterativeMergeSortResultTable) {
        outIterative << row.dataLength << "," << row.chunkSize << "," << row.elapsedTime << "," << row.comparisonCount << "\n";
    }
    outIterative.close();

    return 0;
}
