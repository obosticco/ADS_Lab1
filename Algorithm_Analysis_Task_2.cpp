#include <iostream>
#include <string>
using namespace std;

string convertBase(int p, int b) {
    // Assignment words it weird, but my best guess is that A=10, B=11, C=12,... etc. where p=14 and b=15 should give you E which is 14 in decimal
    string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // The decimal to base 10-36 dictionary
    string result = "";

    while (p > 0) {
        // Basically a dictionary look up using a string and indexes and appends them to the result string
        result = digits[p % b] + result;
        p /= b;
    }
    return result;
}

int main() {
    int p, b;
    cout << "Enter positive integer p: ";
    cin >> p;
    cout << "Enter base b (2-36): ";
    cin >> b;

    cout << "Converted value: " << convertBase(p, b) << endl;
    return 0;
}