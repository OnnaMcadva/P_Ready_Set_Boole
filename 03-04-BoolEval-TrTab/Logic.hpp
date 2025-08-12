#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class PostfixEvaluator {
public:
    bool evalFormula(const std::string &formula);
};

class TruthTableGenerator {
public:
    std::vector<char> extractVariables(const std::string &expr);

    bool evalWithValues(const std::string &expr,
                        const std::unordered_map<char, bool> &values);

    void printTruthTable(const std::string &formula);
};
