#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <algorithm>

std::vector<int> setUnion(const std::vector<int>& a, const std::vector<int>& b) {
    std::set<int> result(a.begin(), a.end());
    result.insert(b.begin(), b.end());
    return std::vector<int>(result.begin(), result.end());
}

std::vector<int> setIntersection(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    std::set<int> sa(a.begin(), a.end());
    std::set<int> sb(b.begin(), b.end());
    std::set_intersection(sa.begin(), sa.end(), sb.begin(), sb.end(), std::back_inserter(result));
    return result;
}

std::vector<int> setSymmetricDifference(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    std::set<int> sa(a.begin(), a.end()), sb(b.begin(), b.end());
    std::set_symmetric_difference(sa.begin(), sa.end(), sb.begin(), sb.end(), std::back_inserter(result));
    return result;
}

std::vector<int> setComplement(const std::vector<int>& a, const std::vector<int>& universe) {
    std::vector<int> result;
    std::set<int> ua(universe.begin(), universe.end());
    std::set<int> sa(a.begin(), a.end());
    std::set_difference(ua.begin(), ua.end(), sa.begin(), sa.end(), std::back_inserter(result));
    return result;
}

std::vector<int> setImplication(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
    // A ⇒ B ≡ ¬A ∪ B
    return setUnion(setComplement(a, universe), b);
}

std::vector<int> setEquivalence(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
    // A ⇔ B ≡ (A ∩ B) ∪ (¬A ∩ ¬B)
    auto not_a = setComplement(a, universe);
    auto not_b = setComplement(b, universe);
    auto a_and_b = setIntersection(a, b);
    auto not_a_and_not_b = setIntersection(not_a, not_b);
    return setUnion(a_and_b, not_a_and_not_b);
}

std::vector<int> evalSet(const std::string& formula, const std::vector<std::vector<int>>& sets) {
    std::vector<int> universe;
    for (const auto& s : sets) {
        universe = setUnion(universe, s);
    }

    std::stack<std::vector<int>> st;
    for (char c : formula) {
        if (c >= 'A' && c <= 'Z') {
            st.push(sets[c - 'A']);
        } else if (c == '!') {
            auto a = st.top(); st.pop();
            st.push(setComplement(a, universe));
        } else {
            auto b = st.top(); st.pop();
            auto a = st.top(); st.pop();
            if (c == '&') st.push(setIntersection(a, b));
            else if (c == '|') st.push(setUnion(a, b));
            else if (c == '^') st.push(setSymmetricDifference(a, b));
            else if (c == '>') st.push(setImplication(a, b, universe));
            else if (c == '=') st.push(setEquivalence(a, b, universe));
            else std::cerr << "Invalid operator: " << c << std::endl;
        }
    }
    return st.empty() ? std::vector<int>() : st.top();
}

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
