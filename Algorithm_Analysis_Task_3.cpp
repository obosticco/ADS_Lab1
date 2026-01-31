#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int binarySearch(const vector<int>& arr, int key) {
    // Binary Searches through an array to find a certain number, returns -1 if number is not in the array.
    // I believe this implementation should work, someone pls double check this
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid; // Found the number
        // Else, update low and high accordingly
        if (arr[mid] < key) low = mid + 1; 
        else high = mid - 1;
    }
    return -1; // Returns -1 if number is not found
}

int interpolationSearch(const vector<int>& arr, int key) {
    // Interpolation Searches through an array to find a certain number, returns -1 if number is not in the array.
    // I am less confident in this one so can someone pls double check this
    int low = 0, high = arr.size() - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) { // If low = high, check if the number is what you're looking for, else, return -1
            if (arr[low] == key) return low;
            return -1;
        }

        int pos = low + ((double)(high - low) /
            (arr[high] - arr[low])) * (key - arr[low]); // Math should be right, someone double check this

        // If found, return position, else update low and high accordingly
        if (arr[pos] == key) return pos; 
        if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// TODO: Someone else implement main and give screenshots so it doesn't look like I did too much work