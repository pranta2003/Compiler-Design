Task 2:


#include <bits/stdc++.h>
using namespace std;

int main() {
    string production;

    cout << "Enter production (example: A->Aa|b): ";
    getline(cin, production);

    // Remove all spaces to make parsing easy
    production.erase(remove(production.begin(), production.end(), ' '), production.end());

    // Left-hand side non-terminal (like 'A')
    char A = production[0];

    // Find position of "->"
    int posArrow = production.find("->");
    if (posArrow == string::npos) {
        cout << "Invalid production format!" << endl;
        return 0;
    }

    // Right-hand side (everything after ->)
    string rhs = production.substr(posArrow + 2);

    bool hasLeftRecursion = false;
    vector<string> alpha; // for Aα (left recursive parts)
    vector<string> beta;  // for β  (non-left-recursive parts)

    // Split RHS by '|' → each part is one production
    string current = "";
    for (int i = 0; i <= (int)rhs.size(); i++) {
        if (i == (int)rhs.size() || rhs[i] == '|') {
            if (!current.empty()) {
                // Check if this part is left recursive: starts with A
                if (current[0] == A) {
                    hasLeftRecursion = true;
                    // Save α (the part after A)
                    alpha.push_back(current.substr(1));
                } else {
                    // Save β
                    beta.push_back(current);
                }
            }
            current = "";
        } else {
            current += rhs[i];
        }
    }

    // -------- Result part --------
    if (!hasLeftRecursion) {
        cout << "\nThis grammar has NO left recursion.\n";
    } else {
        cout << "\nThis grammar HAS left recursion.\n";

        // New productions after removing left recursion
        cout << "\nAfter removing left recursion:\n";

        // A → β A'
        cout << A << " -> ";
        for (int i = 0; i < (int)beta.size(); i++) {
            cout << beta[i] << A << "'";
            if (i != (int)beta.size() - 1) cout << " | ";
        }
        cout << endl;

        // A' → α A' | ε
        cout << A << "' -> ";
        for (int i = 0; i < (int)alpha.size(); i++) {
            cout << alpha[i] << A << "'";
            if (i != (int)alpha.size() - 1) cout << " | ";
        }
        cout << " | ε" << endl;
    }

    return 0;
}
