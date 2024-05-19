#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "headers/drivers.h"
using namespace std;

const string VERSION = "0.0.0";

int main() {

    cout << "\n";

    cout << "> A Blurple Chairs Bashing Tool (v" << VERSION << ")\n"
         << "> made by qua.cc\n\n";

    cout << "Enter the total number of chars: ";
    int total = input(1);

    cout << "Enter your list of chars, each group separated by a space (like bC 2 5): ";
    string rawChars;
    int numChars = 0;
    cin.ignore();
    getline(cin, rawChars);
    for (char ch : rawChars) {
        if (ch != ' ') numChars++;
    }
    while (numChars != total) {
        cout << "You didn't enter " << total << " chars! Re-enter your list of chars: ";
        getline(cin, rawChars);
        for (char ch : rawChars) {
            if (ch != ' ') numChars++;
        }
    }

    int index = 0;
    string chars[total];
    for (int i = 0; i < rawChars.length(); i++){
        if (rawChars[i] != ' ') {
            chars[index] += rawChars[i];
        }
        else index++;
    }

    cout << "\n"
         << "If any, enter the number of fixed char groups (like mzT at pos 5): ";
    int fixed = input(0, total);

    string fixedGroups[fixed];
    int fixedGroupsIndex[fixed];

    /// TODO: verify with the original char array
    if (fixed) {
        for (int i = 0; i < fixed; i++) {
            cout << "\n"
                << "Enter the char group (like mzT): ";
            cin >> fixedGroups[i];
            cout << "Enter the position for " << fixedGroups[i] << " (assuming first letter is pos 1): ";
            fixedGroupsIndex[i] = input(1, total) - 1;
            while (fixedGroupsIndex[i] + fixedGroups[i].length() > total) {
                cout << "Invalid position! Re-enter a new one: ";
                fixedGroupsIndex[i] = input(1, total) - 1;
            }
        }
    }

    cout << "\n"
         << "If any, enter the number of groups that you are 100\% sure on its own order: ";
    int locked = input(0, total - fixed);

    string lockedGroups[locked];

    cout << endl;
    if (locked) {
        for (int i = 0; i < locked; i++) {
            cout << "Enter the char group (like S7): ";   
            cin >> lockedGroups[i];
        }
    }
    cout << endl;

    char charArray[total];
    fill_n(charArray, total, '*');

    for (int i = 0; i < fixed; i++) {
        string group = fixedGroups[i];
        int initialIndex = fixedGroupsIndex[i];
        for (int j = 0; j < group.length(); j++) {
            charArray[initialIndex + j] = group[j];
        }
    }


    char bashChars[total];
    int count = 0;
    for (string str : chars) {
        if (str.empty()) continue;

        int conflict = 0;
        for (string fixedStr : fixedGroups) {
            if (str == fixedStr) conflict = 1;
        }
        for (string lockedStr : lockedGroups) {
            if (str == lockedStr) conflict = 1;
        }
        if (conflict) continue;

        for (int i = 0; i < str.length(); i++) {
            bashChars[count + i] = str[i];
        }
        count += str.length();
    }

    int indexArr[count + locked];
    for (int i = 0; i < count + locked; i++) {
        indexArr[i] = i;
    }
    
    int lockedIndexArr[locked];

    if (locked) {
        for (int i = 0; i < locked; i++) {
            lockedIndexArr[i] = i;
        }
    }

    vector<string> strings;

    do {
        do {
            char tempCharArray[total];
            for (int i = 0; i < total; i++) {
                tempCharArray[i] = charArray[i];
            }

            int possible = 1;
            for (int i : indexArr) {
                string str;
                if (i < count) str = bashChars[i];
                else str = lockedGroups[lockedIndexArr[i - count]];
                int canInsert = 0;
                for (int j = 0; j < total; j++) {
                    int failed = 0;
                    for (int pos = 0; pos < str.length(); pos++) {
                        if ((int) tempCharArray[j + pos] >= 48) { // 48 on ASCII tqble is '0'
                            failed = 1;
                            break;
                        }
                    }
                    if (failed) continue;
                    canInsert = 1;
                    for (int pos = 0; pos < str.length(); pos++) {
                        tempCharArray[j + pos] = str[pos];
                    }
                    break;
                }
                if (!canInsert) possible = 0;
            }
            if (!possible) continue;

            string str = "";
            for (char ch : tempCharArray) {
                if ((int) ch >= 48) str += ch;
            }
            strings.push_back(str);

        } while (next_permutation(lockedIndexArr, lockedIndexArr + locked));
    } while (next_permutation(indexArr, indexArr + count + locked));

    cout << "All strings have been computed!\n"
         << "[ 1 ] Output everything into a local .txt file\n"
         << "[ 2 ] Print into this console window\n"
         << "[   ]\b\b\b";

    int choices[2] = {1, 2};
    int choice = input(choices, sizeof(choices) / sizeof(choices[0]));

    if (choice == 1) {
        ofstream file;
        file.open("strings.txt");
        for (string str : strings) {
            file << str << endl;
        }
        file.close();
        cout << endl
             << "Done!\n";
    }
    else {
        cout << endl;
        for (string str : strings) {
            cout << str << endl;
        }
        cout << endl;
    }

    return 0;
}