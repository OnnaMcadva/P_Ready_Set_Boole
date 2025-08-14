#include "Logic.hpp"
#include <stack>
#include <string>
#include <stdexcept>

bool isVariable(char c) {
    return c >= 'A' && c <= 'Z';
}

bool isOperator(char c) {
    return c == '&' || c == '|' || c == '!' || c == '>' || c == '=';
}

std::string grindItUp(char op, const std::string& left, const std::string& right) {
    if (op == '>') {
        return left + "!" + right + "|";
    } else if (op == '=') {
        std::string part1 = left + right + "&";
        std::string part2 = left + "!" + right + "!" + "&";
        return part1 + part2 + "|";
    }
    throw std::runtime_error("Unknown operator");
}

std::string negate(const std::string& expr) {
    if (expr.size() == 1 && isVariable(expr[0])) {
        return expr + "!";
    }

    char op = expr.back();
    if (op == '!') {
        return expr.substr(0, expr.size() - 1);
    } else if (op == '&' || op == '|') {
        std::stack<std::string> str;
        for (size_t i = 0; i < expr.size() - 1; ++i) {
            char c = expr[i];
            if (isVariable(c)) {
                str.push(std::string(1, c));
            } else if (c == '!') {
                std::string top = str.top(); str.pop();
                str.push(negate(top));
            } else if (c == '&' || c == '|') {
                std::string right = str.top(); str.pop();
                std::string left = str.top(); str.pop();
                str.push(left + right + c);
            } else {
                throw std::runtime_error("Invalid character");
            }
        }
        if (str.size() != 2) {
            throw std::runtime_error("Invalid expression");
        }
        std::string right = str.top(); str.pop();
        std::string left = str.top(); str.pop();

        char new_op = (op == '&') ? '|' : '&';
        return negate(left) + negate(right) + new_op;
    } else {
        throw std::runtime_error("Invalid operator");
    }
}

std::string toNNF(const std::string& formula) {
    std::stack<std::string> string_stack;
    for (char c : formula) {
        if (isVariable(c)) {
            string_stack.push(std::string(1, c));
        } else if (c == '!') {
            if (string_stack.empty()) throw std::runtime_error("Stack underflow on '!'");
            std::string top = string_stack.top(); string_stack.pop();
            string_stack.push(negate(top));
        } else if (c == '&' || c == '|') {
            if (string_stack.size() < 2) throw std::runtime_error("Stack underflow on binary op");
            std::string right = string_stack.top(); string_stack.pop();
            std::string left = string_stack.top(); string_stack.pop();
            string_stack.push(left + right + c);
        } else if (c == '>') {
            if (string_stack.size() < 2) throw std::runtime_error("Stack underflow on '>'");
            std::string right = string_stack.top(); string_stack.pop();
            std::string left = string_stack.top(); string_stack.pop();
            string_stack.push(grindItUp('>', left, right));
        } else if (c == '=') {
            if (string_stack.size() < 2) throw std::runtime_error("Stack underflow on '='");
            std::string right = string_stack.top(); string_stack.pop();
            std::string left = string_stack.top(); string_stack.pop();
            string_stack.push(grindItUp('=', left, right));
        } else {
            throw std::runtime_error(std::string("Unknown character: ") + c);
        }
    }
    if (string_stack.size() != 1) throw std::runtime_error("Invalid formula");
    return string_stack.top();
}

// A | (B & C) → (A | B) & (A | C)
static std::string distributeOrOverAnd(const std::string &left, const std::string &right) {
    if (right.back() == '&') {
        std::string b, c;
        {
            std::stack<std::string> st;
            for (char ch : right) {
                if (isVariable(ch)) {
                    st.push(std::string(1, ch));
                } else if (ch == '&' || ch == '|') {
                    std::string r = st.top(); st.pop();
                    std::string l = st.top(); st.pop();
                    st.push(l + r + ch);
                } else if (ch == '!') {
                    std::string t = st.top(); st.pop();
                    st.push(t + "!");
                }
            }
            if (st.size() != 2) throw std::runtime_error("Invalid right expression for distribution");
            c = st.top(); st.pop();
            b = st.top(); st.pop();
        }
        // (A | B) & (A | C)
        return left + b + "|" + left + c + "|" + "&";
    }
    if (left.back() == '&') {
        std::string a, b;
        {
            std::stack<std::string> st;
            for (char ch : left) {
                if (isVariable(ch)) {
                    st.push(std::string(1, ch));
                } else if (ch == '&' || ch == '|') {
                    std::string r = st.top(); st.pop();
                    std::string l = st.top(); st.pop();
                    st.push(l + r + ch);
                } else if (ch == '!') {
                    std::string t = st.top(); st.pop();
                    st.push(t + "!");
                }
            }
            if (st.size() != 2) throw std::runtime_error("Invalid left expression for distribution");
            b = st.top(); st.pop();
            a = st.top(); st.pop();
        }
        // (A | right) & (B | right)
        return a + right + "|" + b + right + "|" + "&";
    }
    // A | B
    return left + right + "|";
}

// moving & to the end
static std::string moveAndToEnd(const std::string &expr) {
    std::string ors, ands;
    for (char c : expr) {
        if (c == '&') {
            ands.push_back('&');
        } else {
            ors.push_back(c);
        }
    }
    return ors + ands;
}

std::string toCNF(const std::string &formula) {
    std::string r = toNNF(formula);

    //  distr
    std::stack<std::string> st;
    for (char c : r) {
        if (isVariable(c)) {
            st.push(std::string(1, c));
        } else if (c == '!') {
            std::string top = st.top(); st.pop();
            st.push(top + "!");
        } else if (c == '&') {
            std::string right = st.top(); st.pop();
            std::string left = st.top(); st.pop();
            st.push(left + right + "&");
        } else if (c == '|') {
            std::string right = st.top(); st.pop();
            std::string left = st.top(); st.pop();
            st.push(distributeOrOverAnd(left, right));
        }
    }
    if (st.size() != 1) throw std::runtime_error("Invalid CNF conversion");

    return moveAndToEnd(st.top());
}
