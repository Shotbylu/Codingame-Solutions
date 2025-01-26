#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string INVALID_CHARS = "()\t ";
vector<string> CGX;
bool quote = false;
int indentLevel = 0;
size_t index = 0;

void Reformat(const string& s) {
    string str;
    
    for (size_t i = 0; i < s.length(); ++i) {
        char c = s[i];
        string indent(indentLevel * 4, ' ');

        // Handle tab escape sequences
        if (c == '\\' && i + 1 < s.length() && s[i + 1] == 't') {
            str += "    ";
            ++i;
            continue;
        }

        if (quote) {
            str += c;
            if (c == '\'') quote = false; // Toggle quote state
        } else if (INVALID_CHARS.find(c) == string::npos) {
            str += c;
        }

        switch (c) {
            case '\'':
                if (str.empty()) {
                    cout << indent << str;
                    str = "'";
                }
                quote = !quote;
                break;

            case '(':
                if (!str.empty()) {
                    cout << indent << str << endl;
                    str.clear();
                }
                indentLevel++;
                cout << indent << "(\n";
                break;

            case ')':
                if (!str.empty()) {
                    cout << indent << str << endl;
                    str.clear();
                }
                indentLevel = max(0, indentLevel - 1);
                
                if (i < s.length() - 1) {
                    size_t found = s.find_first_not_of(" ", i + 1);
                    if (found != string::npos && s[found] == ';') {
                        cout << indent << ");\n";
                        i = found;
                    } else {
                        cout << indent << ")\n";
                    }
                } else {
                    cout << indent << ")\n";
                }
                break;

            case ';':
                cout << indent << str << endl;
                str.clear();
                break;
        }
    }

    if (!str.empty()) {
        cout << string(indentLevel * 4, ' ') << str;
        if (str.back() != '=') {
            cout << endl;
        } else if (index < CGX.size() - 1) {
            string next = CGX[index + 1];
            size_t found = next.find_first_not_of(" ");
            if (found != string::npos && next[found] == '(') {
                cout << endl;
            }
        }
    }
}

int main() {
    int N;
    cin >> N;
    cin.ignore();

    CGX.resize(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, CGX[i]);
    }

    for (index = 0; index < CGX.size(); ++index) {
        Reformat(CGX[index]);
    }

    return 0;
}
