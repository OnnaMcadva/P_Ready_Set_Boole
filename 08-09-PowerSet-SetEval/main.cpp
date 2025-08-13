#include "SubSets.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <algorithm>

void printPowerSet(const std::vector<std::vector<int>>& ps) {
    std::cout << "{\n";
    for (const auto& subset : ps) {
        std::cout << "  {";
        for (size_t i = 0; i < subset.size(); ++i) {
            std::cout << subset[i];
            if (i + 1 < subset.size())
                std::cout << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "}\n";
}

void printSet(const std::vector<int>& set) {
    std::cout << "{ ";
    for (int n : set) std::cout << n << " ";
    std::cout << "}" << std::endl;
}

int main() {
    std::vector<int> input = {1, 2, 3, 5};
    std::cout << "\n✨ Powerset ✨\n" << std::endl;
    printSet(input);
    auto ps = powerSet(input);
    printPowerSet(ps);

    std::cout << "\n✨ Set evaluation ✨\n" << std::endl;

    {
        std::vector<std::vector<int>> sets = {{0, 1, 2}, {0, 3, 4}};
        auto result = evalSet("AB&", sets);
        printSet(result); // { 0 }
    }
    {
        std::vector<std::vector<int>> sets = {{0, 1, 2}, {0, 3, 4}};
        auto result = evalSet("AB|", sets);
        printSet(result); // { 0, 1, 2, 3, 4 }
    }
    {
        std::vector<std::vector<int>> sets = {{0, 1, 2}, {0, 3, 4}};
        auto result = evalSet("A!", sets);
        printSet(result); // { 3, 4 }
    }

    return 0;
}
