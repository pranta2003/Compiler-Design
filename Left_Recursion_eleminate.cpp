#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string input;
    cout << "Enter grammar (example: A->Aa|b): ";
    getline(cin, input);

    // Remove spaces
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // Find "->"
    int pos = input.find("->");
    if (pos == string::npos) {
        cout << "Invalid grammar format! Use like A->Aa|b" << endl;
        return 0;
    }

    string left = input.substr(0, pos);
    string right = input.substr(pos + 2);

    // Split RHS by '|'
    vector<string> productions;
    string temp = "";
    for (char c : right) {
        if (c == '|') {
            if (!temp.empty()) productions.push_back(temp);
            temp = "";
        } else temp += c;
    }
    if (!temp.empty()) productions.push_back(temp);

    // Separate α (left-recursive) and β (non-left-recursive)
    vector<string> alpha, beta;
    for (string p : productions) { // works in C++11+
        if (!p.empty() && p[0] == left[0])  // left recursion
            alpha.push_back(p.substr(1));
        else
            beta.push_back(p);
    }

    // If no left recursion found
    if (alpha.empty()) {
        cout << "No Left Recursion found!" << endl;
        return 0;
    }

    cout << "Left recursion detected!" << endl;
    cout << "After elimination:" << endl;

    string newVar = left + "'";

    // A -> βA'
    cout << left << " -> ";
    for (size_t i = 0; i < beta.size(); ++i) {
        cout << beta[i] << newVar;
        if (i != beta.size() - 1) cout << " | ";
    }
    cout << endl;

    // A' -> αA' | ε
    cout << newVar << " -> ";
    for (size_t i = 0; i < alpha.size(); ++i) {
        cout << alpha[i] << newVar;
        if (i != alpha.size() - 1) cout << " | ";
    }
    cout << " | ε" << endl;

    return 0;
}
