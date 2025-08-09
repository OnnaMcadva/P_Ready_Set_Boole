#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <bitset>

bool eval(const std::string &expr, const std::unordered_map<char, bool> &values) {
    std::stack<bool> bool_stack;

    for (char c : expr) {
        if (c >= 'A' && c <= 'Z') {
            bool_stack.push(values.at(c));
        } else if (c == '!') {
            if (bool_stack.empty()) {
                std::cerr << "Error: Not enough operands for '!' operator." << std::endl;
                return false;
            }
            bool a = bool_stack.top(); bool_stack.pop();
            bool_stack.push(!a);
        } else {
            if (bool_stack.size() < 2) {
                std::cerr << "Error: Not enough operands for binary operator '" << c << "'." << std::endl;
                return false;
            }
            bool b = bool_stack.top(); bool_stack.pop();
            bool a = bool_stack.top(); bool_stack.pop();

            if (c == '&') bool_stack.push(a && b);
            else if (c == '|') bool_stack.push(a || b);
            else if (c == '^') bool_stack.push(a != b);
            else if (c == '>') bool_stack.push(!a || b);
            else if (c == '=') bool_stack.push(a == b);
            else {
                std::cerr << "Error: Unknown operator '" << c << "'." << std::endl;
                return false;
            }
        }
    }

    if (bool_stack.size() != 1) {
        std::cerr << "🤖 Invalid formula: Look into the Stack 👿" << std::endl;
        exit(1);
    }

    return bool_stack.top();
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

void printTruthTable(const std::string &formula) {
    std::vector<char> uniq_vars = getVar(formula);
    int n = uniq_vars.size();
    int total = 1 << n;

    for (char v : uniq_vars)
        std::cout << "| " << v << " ";
    std::cout << "| = |\n";
    for (int i = 0; i < uniq_vars.size() + 1; i++)
        std::cout << "|---";
    std::cout << "|\n";

    for (int i = 0; i < total; i++) {
        std::unordered_map<char, bool> values;
        for (int j = 0; j < n; j++) {
            bool val = (i >> (n - j - 1)) & 1;
            values[uniq_vars[j]] = val;
            std::cout << "| " << val << " ";
        }
        bool result = eval(formula, values);
        std::cout << "| " << result << " |\n";
    }
}

// int main() {
//     std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡" << "\n";
//     std::string formula = "AB&C|";
//     printTruthTable(formula);
//     std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡" << "\n";
//     formula = "AB>";
//     printTruthTable(formula);
//     std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡" << "\n";
//     formula = "AB&A>";
//     printTruthTable(formula);
//     std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡" << "\n";
//     return 0;
// }