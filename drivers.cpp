#include <iostream>
#include <algorithm>
#include <vector>
#include "headers/drivers.h"
using namespace std;

int input(int arr[], int arrSize) {
    int n;
    cin >> n;
    int *iterator = find(&arr[0], arr + arrSize, n);
    while (!cin.good() || (iterator - arr > arrSize)) {
        if (!cin.good()) {
            cin.clear();
            string str;
            cin >> str;
        }
        cout << "Invalid response, enter something new: ";
        cin >> n;
    }
    return n;
}

int input(int lb, int ub) {
    int n;
    cin >> n;
    while (!cin.good() || n < lb || n > ub) {
        if (!cin.good()) {
            cin.clear();
            string str;
            cin >> str;
        }
        cout << "Invalid response, enter something new: ";
        cin >> n;
    }
    return n;
}