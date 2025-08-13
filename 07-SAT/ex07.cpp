#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

bool evalFormula(const std::string& formula, const std::vector<bool>& values, const std::vector<char>& vars) {
    std::stack<bool> bool_stack;

    for (char c : formula) {
        if (std::isalpha(c)) {
            auto it = std::find(vars.begin(), vars.end(), c);
            if (it == vars.end()) return false;
            bool_stack.push(values[it - vars.begin()]);
        }
        else {
            if (c == '!') {
                if (bool_stack.empty()) return false;
                bool a = bool_stack.top(); bool_stack.pop();
                bool_stack.push(!a);
            }
            else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=') {
                if (bool_stack.size() < 2) return false;
                bool b = bool_stack.top(); bool_stack.pop();
                bool a = bool_stack.top(); bool_stack.pop();
                bool res = false;

                if (c == '&') res = a && b;
                else if (c == '|') res = a || b;
                else if (c == '^') res = a != b;
                else if (c == '>') res = (!a) || b;
                else if (c == '=') res = (a == b);

                bool_stack.push(res);
            }
            else {
                return false;
            }
        }
    }
    return (bool_stack.size() == 1) ? bool_stack.top() : false;
}

bool sat(const std::string& formula) {
    std::set<char> var_set;
    for (char c : formula) {
        if (std::isalpha(c)) var_set.insert(c);
    }
    std::vector<char> vars(var_set.begin(), var_set.end());
    int n = vars.size();
    if (n == 0) {
        std::vector<bool> empty;
        return evalFormula(formula, empty, vars);
    }

    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<bool> values(n);
        for (int i = 0; i < n; ++i) {
            values[i] = (mask >> i) & 1;
        }
        if (evalFormula(formula, values, vars)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << sat("AB|") << "\n";     // true
    std::cout << sat("AB&") << "\n";     // true
    std::cout << sat("AA!&") << "\n";    // false
    std::cout << sat("AA^") << "\n";     // false
    std::cout << sat("AB>") << "\n";     // true
    std::cout << sat("AB=") << "\n";     // true
    std::cout << sat("As^") << "\n";     // true
}
