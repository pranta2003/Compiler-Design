#include <bits/stdc++.h>
using namespace std;

// ---------- Global Data ----------
map<char, vector<string>> prod;   // productions: A -> list of RHS strings
map<char, set<char>> FIRST, FOLLOW;
set<char> nonTerminals;
char startSymbol;                 // first non-terminal will be start

bool isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// ---------- FIRST ----------

set<char> firstOf(char X);            // forward declaration

// FIRST of a string (like "TA", "(E)", "e")
set<char> firstOfString(const string &s) {
    set<char> result;

    // empty string, shouldn't happen in our input
    if (s.size() == 0) return result;

    bool allEpsilon = true;

    for (int i = 0; i < (int)s.size(); i++) {
        char ch = s[i];

        // if ch is terminal or epsilon
        if (!isNonTerminal(ch)) {
            if (ch != 'e') result.insert(ch);   // normal terminal
            else result.insert('e');            // epsilon
            allEpsilon = (ch == 'e');          // true only if epsilon
            break;                             // terminal stops further
        } else {
            // ch is non-terminal
            set<char> f = firstOf(ch);
            bool hasEpsilon = false;
            for (char x : f) {
                if (x == 'e') hasEpsilon = true;
                else result.insert(x);
            }
            if (!hasEpsilon) {                 // cannot go further
                allEpsilon = false;
                break;
            }
            // else: epsilon present, so continue to next symbol
        }
    }

    if (allEpsilon) result.insert('e');
    return result;
}

// FIRST of a single symbol (non-terminal or terminal)
set<char> firstOf(char X) {
    // if already computed, just return
    if (!FIRST[X].empty()) return FIRST[X];

    set<char> result;

    // terminal
    if (!isNonTerminal(X)) {
        result.insert(X);
        FIRST[X] = result;
        return result;
    }

    // non-terminal: look at its productions
    for (string rhs : prod[X]) {
        if (rhs == "e") {              // epsilon production
            result.insert('e');
            continue;
        }
        set<char> temp = firstOfString(rhs);
        for (char c : temp) result.insert(c);
    }

    FIRST[X] = result;
    return result;
}

// ---------- FOLLOW ----------

void computeFOLLOW() {
    // start symbol gets $
    FOLLOW[startSymbol].insert('$');

    bool changed = true;
    while (changed) {
        changed = false;

        // for each production A -> rhs
        for (auto &p : prod) {
            char A = p.first;
            for (string rhs : p.second) {
                int n = rhs.size();

                for (int i = 0; i < n; i++) {
                    char B = rhs[i];
                    if (!isNonTerminal(B)) continue;

                    // look at beta = suffix after B
                    string beta = rhs.substr(i + 1);

                    set<char> addToFollow;

                    if (beta.size() == 0) {
                        // nothing after B → add FOLLOW(A)
                        addToFollow = FOLLOW[A];
                    } else {
                        // FIRST(beta)
                        set<char> firstBeta = firstOfString(beta);
                        bool hasEpsilon = false;
                        for (char c : firstBeta) {
                            if (c == 'e') hasEpsilon = true;
                            else addToFollow.insert(c);
                        }
                        if (hasEpsilon) {
                            // also add FOLLOW(A)
                            for (char c : FOLLOW[A]) addToFollow.insert(c);
                        }
                    }

                    // actually insert into FOLLOW(B)
                    int oldSize = FOLLOW[B].size();
                    for (char c : addToFollow) FOLLOW[B].insert(c);
                    if ((int)FOLLOW[B].size() > oldSize) changed = true;
                }
            }
        }
    }
}

// ---------- MAIN ----------

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Use format A=alpha1|alpha2 (epsilon as e)\n";
    cout << "Example: E=TA\n";
    cout << "         A=+TA|e\n\n";

    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;          // e.g. E=TA|Tb
        char lhs = line[0];
        if (i == 0) startSymbol = lhs;
        nonTerminals.insert(lhs);

        string rhsPart = line.substr(2);   // after '='
        string current = "";
        for (char c : rhsPart) {
            if (c == '|') {
                prod[lhs].push_back(current);
                current = "";
            } else {
                current += c;
            }
        }
        if (!current.empty()) prod[lhs].push_back(current);
    }

    // compute FIRST for all non-terminals
    for (char A : nonTerminals) {
        firstOf(A);
    }

    // compute FOLLOW
    computeFOLLOW();

    // --------- OUTPUT ---------
    cout << "\nFIRST sets:\n";
    for (char A : nonTerminals) {
        cout << "FIRST(" << A << ") = { ";
        for (char c : FIRST[A]) {
            if (c == 'e') cout << "ε ";
            else cout << c << ' ';
        }
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char A : nonTerminals) {
        cout << "FOLLOW(" << A << ") = { ";
        for (char c : FOLLOW[A]) {
            if (c == '$') cout << "$ ";
            else cout << c << ' ';
        }
        cout << "}\n";
    }

    return 0;
}
