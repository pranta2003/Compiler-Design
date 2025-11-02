#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string input;
    cout << "Enter grammar (example: A->Aa|b): ";
    getline(cin, input);

    // Split LHS and RHS
    int pos = input.find("->");
    string left = input.substr(0, pos);
    string right = input.substr(pos + 2);

    // Split RHS by '|'
    vector<string> prod;
    string temp = "";
    for (char c : right) {
        if (c == '|') {
            prod.push_back(temp);
            temp = "";
        } else temp += c;
    }
    prod.push_back(temp);

    // Separate alpha and beta
    vector<string> alpha, beta;
    for (string p : prod) {
        if (p[0] == left[0]) // Left recursion
            alpha.push_back(p.substr(1));
        else
            beta.push_back(p);
    }

    // Check if left recursion exists
    if (alpha.empty()) {
        cout << "No Left Recursion.\n";
        return 0;
    }

    cout << "Left recursion detected!\n";
    cout << "After elimination:\n";

    string newVar = left + "'";

    // A -> βA'
    cout << left << " -> ";
    for (int i = 0; i < beta.size(); i++) {
        cout << beta[i] << newVar;
        if (i != beta.size() - 1) cout << " | ";
    }
    cout << endl;

    // A' -> αA' | ε
    cout << newVar << " -> ";
    for (int i = 0; i < alpha.size(); i++) {
        cout << alpha[i] << newVar;
        if (i != alpha.size() - 1) cout << " | ";
    }
    cout << " | ε\n";

    return 0;
}
