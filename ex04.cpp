#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <bitset>

bool eval(const std::string &expr, const std::unordered_map<char, bool> &values) {
    std::stack<bool> st;

    for (char c : expr) {
        if (c >= 'A' && c <= 'Z') {
            st.push(values.at(c));
        } else if (c == '!') {
            bool a = st.top(); st.pop();
            st.push(!a);
        } else {
            bool b = st.top(); st.pop();
            bool a = st.top(); st.pop();
            if (c == '&') st.push(a && b);
            else if (c == '|') st.push(a || b);
            else if (c == '^') st.push(a != b);
            else if (c == '>') st.push(!a || b);
            else if (c == '=') st.push(a == b);
            else {
                std::cerr << "Unknown operator: " << c << std::endl;
                return false;
            }
        }
    }

    return st.top();
}

std::vector<char> getVar(const std::string &expr) {
    std::unordered_set<char> var_set;
    for (char c : expr) {
        if (c >= 'A' && c <= 'Z') {
            var_set.insert(c);
        }
    }
    std::vector<char> vars(var_set.begin(), var_set.end());
    std::sort(vars.begin(), vars.end());
    return vars;
}

void printTruthTable(const std::string &expr) {
    std::vector<char> vars = getVar(expr);
    int n = vars.size();
    int total = 1 << n;

    for (char v : vars)
        std::cout << "| " << v << " ";
    std::cout << "| = |\n";
    for (int i = 0; i < vars.size() + 1; i++)
        std::cout << "|---";
    std::cout << "|\n";

    for (int i = 0; i < total; i++) {
        std::unordered_map<char, bool> values;
        for (int j = 0; j < n; j++) {
            bool val = (i >> (n - j - 1)) & 1;
            values[vars[j]] = val;
            std::cout << "| " << val << " ";
        }
        bool result = eval(expr, values);
        std::cout << "| " << result << " |\n";
    }
}

// int main() {
//     std::string formula = "AB&C|";
//     printTruthTable(formula);
//     return 0;
// }