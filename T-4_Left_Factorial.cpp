#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find common prefix of two strings
string commonPrefix(const string &a, const string &b) {
    string pref = "";
    int n = min(a.size(), b.size());
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            pref += a[i];
        } else {
            break;
        }
    }
    return pref;
}

int main() {
    string nonTerminal;
    int n;

    cout << "Enter non-terminal (like E, A, S): ";
    cin >> nonTerminal;

    cout << "Enter number of productions: ";
    cin >> n;

    vector<string> prod(n);
    cout << "Enter productions (right side only, no spaces):\n";
    for (int i = 0; i < n; i++) {
        cout << nonTerminal << " -> ";
        cin >> prod[i];
    }

    // Step 1: Find common prefix of ALL productions
    string prefix = prod[0];
    for (int i = 1; i < n; i++) {
        prefix = commonPrefix(prefix, prod[i]);
        if (prefix == "") break; // no common prefix
    }

    if (prefix == "") {
        cout << "\nGrammar is already LEFT FACTORED (no common prefix).\n";
        cout << "Given grammar:\n";
        for (int i = 0; i < n; i++) {
            cout << nonTerminal << " -> " << prod[i] << "\n";
        }
    } else {
        cout << "\nGrammar is NOT left factored.\n";
        cout << "Common prefix = \"" << prefix << "\"\n";

        // We will create a new non-terminal: A'
        string newNonTerminal = nonTerminal + "'";

        cout << "\nAfter LEFT FACTORING:\n";

        // First production line: A -> prefix A'
        cout << nonTerminal << " -> " << prefix << newNonTerminal << "\n";

        // Build productions of A'
        cout << newNonTerminal << " -> ";

        bool first = true;
        for (int i = 0; i < n; i++) {
            string rest = prod[i].substr(prefix.size()); // remaining part after prefix

            if (rest == "") {
                // If production is exactly the prefix, we use epsilon
                if (!first) cout << " | ";
                cout << "epsilon";
                first = false;
            } else {
                if (!first) cout << " | ";
                cout << rest;
                first = false;
            }
        }
        cout << "\n";
    }

    return 0;
}
