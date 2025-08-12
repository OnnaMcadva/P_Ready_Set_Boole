#include <iostream>
#include <vector>

std::vector<std::vector<int>> powerSet(const std::vector<int>& set) {
    std::vector<std::vector<int>> result;
    size_t n = set.size();
    size_t total = 1 << n;

    for (size_t mask = 0; mask < total; ++mask) {
        std::vector<int> subset;
        for (size_t i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(set[i]);
            }
        }
        result.push_back(subset);
    }
    return result;
}

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

int main() {
    std::vector<int> input = {1, 2, 3, 5};
    auto ps = powerSet(input);
    printPowerSet(ps);

    return 0;
}
