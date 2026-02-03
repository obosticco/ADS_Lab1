#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

volatile int sink;

int rightToLeft(int x, int n) {
    int result = 1;
    while (n > 0) {
        if (n & 1)
            result *= x;
        x *= x;
        n >>= 1;
    }
    return result;
}

int leftToRight(int x, int n) {
    int result = 1;
    int bits[32];
    int count = 0;

    while (n > 0) {
        bits[count++] = n & 1;
        n >>= 1;
    }

    for (int i = count - 1; i >= 0; i--) {
        result *= result;
        if (bits[i] == 1)
            result *= x;
    }
    return result;
}

int main() {
    int x = 2;

    vector<int> testN = {
        1, 2, 5, 10, 20, 50, 100, 200,
        500, 1000, 2000, 5000, 10000,
        20000, 50000, 100000, 200000,
        500000, 1000000, 2000000
    };

    const int ITERATIONS = 1000000;

    cout << "\n n\tRTL (ns)\tLTR (ns)\n";

    for (int n : testN) {

        auto start = high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; i++)
            sink = rightToLeft(x, n);
        auto end = high_resolution_clock::now();
        auto rtlTime = duration_cast<nanoseconds>(end - start).count();

        start = high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; i++)
            sink = leftToRight(x, n);
        end = high_resolution_clock::now();
        auto ltrTime = duration_cast<nanoseconds>(end - start).count();

        cout << n << "\t"
             << rtlTime / ITERATIONS << "\t\t"
             << ltrTime / ITERATIONS << endl;
    }
}