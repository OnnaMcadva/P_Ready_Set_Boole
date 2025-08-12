#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <algorithm>

std::vector<int> set_union(const std::vector<int>& a, const std::vector<int>& b) {
    std::set<int> result(a.begin(), a.end());
    result.insert(b.begin(), b.end());
    return std::vector<int>(result.begin(), result.end());
}

std::vector<int> set_intersection(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    std::set<int> sa(a.begin(), a.end());
    std::set<int> sb(b.begin(), b.end());
    std::set_intersection(sa.begin(), sa.end(), sb.begin(), sb.end(), std::back_inserter(result));
    return result;
}

std::vector<int> set_symmetric_difference(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    std::set<int> sa(a.begin(), a.end()), sb(b.begin(), b.end());
    std::set_symmetric_difference(sa.begin(), sa.end(), sb.begin(), sb.end(), std::back_inserter(result));
    return result;
}

std::vector<int> set_complement(const std::vector<int>& a, const std::vector<int>& universe) {
    std::vector<int> result;
    std::set<int> ua(universe.begin(), universe.end());
    std::set<int> sa(a.begin(), a.end());
    std::set_difference(ua.begin(), ua.end(), sa.begin(), sa.end(), std::back_inserter(result));
    return result;
}

std::vector<int> set_implication(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
    // A ⇒ B ≡ ¬A ∪ B
    return set_union(set_complement(a, universe), b);
}

std::vector<int> set_equivalence(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
    // A ⇔ B ≡ (A ∩ B) ∪ (¬A ∩ ¬B)
    auto not_a = set_complement(a, universe);
    auto not_b = set_complement(b, universe);
    auto a_and_b = set_intersection(a, b);
    auto not_a_and_not_b = set_intersection(not_a, not_b);
    return set_union(a_and_b, not_a_and_not_b);
}

std::vector<int> eval_set(const std::string& formula, const std::vector<std::vector<int>>& sets) {
    std::vector<int> universe;
    for (const auto& s : sets) {
        universe = set_union(universe, s);
    }

    std::stack<std::vector<int>> st;
    for (char c : formula) {
        if (c >= 'A' && c <= 'Z') {
            st.push(sets[c - 'A']);
        } else if (c == '!') {
            auto a = st.top(); st.pop();
            st.push(set_complement(a, universe));
        } else {
            auto b = st.top(); st.pop();
            auto a = st.top(); st.pop();
            if (c == '&') st.push(set_intersection(a, b));
            else if (c == '|') st.push(set_union(a, b));
            else if (c == '^') st.push(set_symmetric_difference(a, b));
            else if (c == '>') st.push(set_implication(a, b, universe));
            else if (c == '=') st.push(set_equivalence(a, b, universe));
            else std::cerr << "Invalid operator: " << c << std::endl;
        }
    }
    return st.empty() ? std::vector<int>() : st.top();
}

void print_set(const std::vector<int>& set) {
    std::cout << "{ ";
    for (int n : set) std::cout << n << " ";
    std::cout << "}" << std::endl;
}

int main() {
    {
        std::vector<std::vector<int>> sets = {{0, 1, 2}, {0, 3, 4}};
        auto result = eval_set("AB&", sets);
        print_set(result); // { 0 }
    }
    {
        std::vector<std::vector<int>> sets = {{0, 1, 2}, {3, 4, 5}};
        auto result = eval_set("AB|", sets);
        print_set(result); // { 0, 1, 2, 3, 4, 5 }
    }
    {
        std::vector<std::vector<int>> sets = {{0, 1, 2}};
        auto result = eval_set("A!", sets);
        print_set(result); // {}
    }
    return 0;
}