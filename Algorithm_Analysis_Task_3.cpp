#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// Simple benchmark comparing Binary Search and Interpolation Search
// Arrays are randomly generated, sorted, and searched multiple times
// Timing is averaged to smooth out noise

/*
 * Binary Search
 * Inputs: sorted array, search value, size of array
 * Output: index if found, -1 otherwise
 */
int binarySearch(const vector<int> &arr, int key, int size)
{
    int low = 0;
    int high = size - 1;

    // Repeatedly narrow the search range by half
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

/*
 * Interpolation Search
 * Inputs: sorted array, search value, size of array
 * Output: index if found, -1 otherwise
 */
int interpolationSearch(const vector<int> &arr, int key, int size)
{
    int low = 0;
    int high = size - 1;

    // Continue while the key is within the current value range
    while (low <= high && key >= arr[low] && key <= arr[high])
    {
        // Prevent divide-by-zero when values are identical
        if (arr[low] == arr[high])
        {
            return (arr[low] == key) ? low : -1;
        }

        // Estimate likely position of key based on value distribution
        long long pos = low +
                        ((long long)(key - arr[low]) * (high - low)) /
                            (arr[high] - arr[low]);

        if (pos < low)
            pos = low;
        if (pos > high)
            pos = high;

        if (arr[pos] == key)
            return pos;
        if (arr[pos] < key)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

/*
 * Generates a sorted array of random integers
 * Sorting is required before binary or interpolation search
 */
vector<int> generateSortedArray(int size, int minVal, int maxVal, mt19937 &rng)
{
    vector<int> arr(size);
    uniform_int_distribution<int> dist(minVal, maxVal);

    for (int i = 0; i < size; i++)
        arr[i] = dist(rng);

    sort(arr.begin(), arr.end());
    return arr;
}

int main()
{
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));

    // Different input sizes to observe scaling behavior
    vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000};
    const int trials = 20000;
    const int minVal = 0;
    const int maxVal = 100000;

    cout << "\nBinary Search vs Interpolation Search Benchmark\n";
    cout << "Trials per size: " << trials << " (50% hit / 50% miss)\n\n";

    cout << left
         << setw(10) << "Size"
         << setw(20) << "Binary avg (ns)"
         << setw(20) << "Interp avg (ns)"
         << "\n";
    cout << string(50, '-') << "\n";

    for (int n : sizes)
    {
        vector<int> arr = generateSortedArray(n, minVal, maxVal, rng);

        uniform_int_distribution<int> idxDist(0, n - 1);
        uniform_int_distribution<int> coin(0, 1);

        long long binTotal = 0;
        long long intTotal = 0;
        volatile int sink = 0;

        // Run multiple searches to get an average runtime
        for (int i = 0; i < trials; i++)
        {
            bool hit = coin(rng);
            int key = hit ? arr[idxDist(rng)]
                          : (coin(rng) ? arr.front() - 1 : arr.back() + 1);

            auto bStart = chrono::high_resolution_clock::now();
            sink ^= binarySearch(arr, key, n);
            auto bEnd = chrono::high_resolution_clock::now();
            binTotal += chrono::duration_cast<chrono::nanoseconds>(bEnd - bStart).count();

            auto iStart = chrono::high_resolution_clock::now();
            sink ^= interpolationSearch(arr, key, n);
            auto iEnd = chrono::high_resolution_clock::now();
            intTotal += chrono::duration_cast<chrono::nanoseconds>(iEnd - iStart).count();
        }

        cout << left
             << setw(10) << n
             << setw(20) << fixed << setprecision(1) << (double)binTotal / trials
             << setw(20) << fixed << setprecision(1) << (double)intTotal / trials
             << "\n";
    }

    return 0;
}