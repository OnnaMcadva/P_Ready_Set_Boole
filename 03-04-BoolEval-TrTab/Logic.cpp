#include "Logic.hpp"
#include <iostream>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>

bool applyOperator(char op, bool a, bool b = false) {
    switch (op) {
        case '!': return !a;
        case '&': return a && b;
        case '|': return a || b;
        case '^': return a ^ b;
        case '>': return !a || b;
        case '=': return a == b;
        default:
            std::cerr << "👿 Unknown operator: " << op << std::endl;
            exit(1);
    }
}

bool evalPostfix(const std::string &formula,
                 const std::function<bool(char)> &valueProvider) {
    std::stack<bool> bool_stack;

    for (char c : formula) {
        if ((c >= 'A' && c <= 'Z') || c == '0' || c == '1') {
            bool_stack.push(valueProvider(c));
        } else if (c == '!') {
            if (bool_stack.empty()) {
                std::cerr << "🤖 Not enough operands for '!' 🐬" << std::endl;
                exit(1);
            }
            bool a = bool_stack.top(); bool_stack.pop();
            bool_stack.push(applyOperator('!', a));
        } else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=') {
            if (bool_stack.size() < 2) {
                std::cerr << "🤖 Not enough operands for '" << c << "' 🐬" << std::endl;
                exit(1);
            }
            bool b = bool_stack.top(); bool_stack.pop();
            bool a = bool_stack.top(); bool_stack.pop();
            bool_stack.push(applyOperator(c, a, b));
        } else {
            std::cerr << "🤖 Invalid character: '" << c << "' 🌳" << std::endl;
            exit(1);
        }
    }

    if (bool_stack.size() != 1) {
        std::cerr << "🤖 Invalid formula: Look into the Stack 👿" << std::endl;
        exit(1);
    }

    return bool_stack.top();
}

// ===== PostfixEvaluator =====
bool PostfixEvaluator::evalFormula(const std::string &formula) {
    return evalPostfix(formula, [](char c) {
        if (c == '0') return false;
        if (c == '1') return true;
        std::cerr << "🤖 Unexpected variable in PostfixEvaluator: " << c << std::endl;
        exit(1);
    });
}

// ===== TruthTableGenerator =====
std::vector<char> TruthTableGenerator::extractVariables(const std::string &expr) {
    std::unordered_set<char> varSet;
    for (char c : expr) {
        if (c >= 'A' && c <= 'Z') varSet.insert(c);
    }
    std::vector<char> result(varSet.begin(), varSet.end());
    std::sort(result.begin(), result.end());
    return result;
}

bool TruthTableGenerator::evalWithValues(const std::string &expr,
                                         const std::unordered_map<char, bool> &values) {
    return evalPostfix(expr, [&](char c) {
        if (c >= 'A' && c <= 'Z') return values.at(c);
        if (c == '0') return false;
        if (c == '1') return true;
        std::cerr << "🤖 Unexpected character in TruthTableGenerator: " << c << std::endl;
        exit(1);
    });
}

void TruthTableGenerator::printTruthTable(const std::string &formula) {
    std::vector<char> vars = extractVariables(formula);
    int n = vars.size();
    int total = 1 << n;

    for (char v : vars) std::cout << "| " << v << " ";
    std::cout << "| = |\n";

    for (size_t i = 0; i < vars.size() + 1; i++) std::cout << "|---";
    std::cout << "|\n";

    for (int mask = 0; mask < total; mask++) {
        std::unordered_map<char, bool> values;
        for (int j = 0; j < n; j++) {
            bool val = (mask >> (n - j - 1)) & 1;
            values[vars[j]] = val;
            std::cout << "| " << val << " ";
        }
        bool res = evalWithValues(formula, values);
        std::cout << "| " << res << " |\n";
    }
}
