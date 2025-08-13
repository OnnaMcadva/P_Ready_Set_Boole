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

// #include "../main.hpp"
// #include "../utils/params.hpp"

// using std::string;

// // Проверка оператора
// static bool is_operator(char c) {
//     return c == '&' || c == '|';
// }

// // Перестановка для вида ab&c& => abc&&
// static string handle_and_and(const ParamSet& ps) {
//     const string& a = ps.left->left->value;
//     const string& b = ps.left->right->value;
//     const string& c = ps.right->value;
//     return c + "&&";
// }

// // Перестановка для вида abc&| => ab|ac|b&
// static string handle_or_and_right(const ParamSet& ps) {
//     const string& a = ps.left->value;
//     const string& b = ps.right->left->value;
//     const string& c = ps.right->right->value;
//     return "|" + a + c + "|" + b + "&";
// }

// // Перестановка для вида bc&a| => ab|ac|b&
// static string handle_or_and_left(const ParamSet& ps) {
//     const string& a = ps.left->value;
//     const string& b = ps.right->left->value;
//     const string& c = ps.right->right->value;
//     return a + b + "|" + a + c + "|" + b + "&";
// }

// // Основная функция для сдвига и перестановки
// static string move_and_back(const string& s) noexcept {
//     string r;
//     for (size_t i = 0; i < s.length(); ++i) {
//         r.push_back(s[i]);
//         if (!is_operator(s[i])) continue;

//         auto ps = get_params(r, r.length() - 1);
//         auto& le = *(ps.left);
//         auto& ri = *(ps.right);

//         string new_piece;

//         if (ps.value.back() == '&' && le.value.back() == '&') {
//             // ab&c& => abc&&
//             r = r.substr(0, r.length() - (ri.value.length() + 2));
//             new_piece = handle_and_and(ps);
//         } 
//         else if (ps.value.back() == '|' && ri.value.back() == '&') {
//             // abc&| => ab|ac|b&
//             r = r.substr(0, r.length() - (ri.value.length() + 2));
//             new_piece = handle_or_and_right(ps);
//         } 
//         else if (ps.value.back() == '|' && le.value.back() == '&') {
//             // bc&a| => ab|ac|b&
//             r = r.substr(0, r.length() - ps.value.length());
//             new_piece = handle_or_and_left(ps);
//         }

//         r += new_piece;
//     }
//     return r;
// }

// // Проверка корректности CNF
// static bool is_valid(const string& r) noexcept {
//     bool and_zone = true;
//     for (auto it = r.rbegin(); it != r.rend(); ++it) {
//         if (*it == '&' && !and_zone) return false;
//         if (*it == '&') continue;
//         and_zone = false;
//     }
//     return true;
// }

// // Конечная функция для CNF
// string conjunctive_normal_form(const string& formula) {
//     string r = negation_normal_form(formula);
//     while (!is_valid(r)) {
//         r = move_and_back(r);
//     }
//     return r;
// }


// #include "../main.hpp"
// #include "../utils/params.hpp"

// using std::string;

// // Проверка оператора
// static bool is_operator(char c) {
//     return c == '&' || c == '|';
// }

// // Перестановка для ab&c& => abc&&
// static string handle_and_and(const ParamSet& ps) {
//     const string& a = ps.left->left->value;
//     const string& b = ps.left->right->value;
//     const string& c = ps.right->value;
//     return a + b + c + "&&";
// }

// // Перестановка для abc&| => ab|ac|b&
// static string handle_or_and_right(const ParamSet& ps) {
//     const string& a = ps.left->value;
//     const string& b = ps.right->left->value;
//     const string& c = ps.right->right->value;
//     return a + b + "|" + a + c + "|" + b + "&";
// }

// // Перестановка для bc&a| => ab|ac|b&
// static string handle_or_and_left(const ParamSet& ps) {
//     const string& a = ps.left->value;
//     const string& b = ps.right->left->value;
//     const string& c = ps.right->right->value;
//     return a + b + "|" + a + c + "|" + b + "&";
// }

// // Функциональный вариант move_and_back
// static string move_and_back(const string& s) noexcept {
//     string result;
//     size_t i = 0;

//     while (i < s.length()) {
//         result.push_back(s[i]);
//         if (!is_operator(s[i])) {
//             ++i;
//             continue;
//         }

//         ParamSet ps = get_params(result, result.length() - 1);
//         string new_piece;

//         if (ps.value.back() == '&' && ps.left->value.back() == '&') {
//             new_piece = handle_and_and(ps);
//             result = result.substr(0, result.length() - (ps.right->value.length() + 2)) + new_piece;
//         }
//         else if (ps.value.back() == '|' && ps.right->value.back() == '&') {
//             new_piece = handle_or_and_right(ps);
//             result = result.substr(0, result.length() - (ps.right->value.length() + 2)) + new_piece;
//         }
//         else if (ps.value.back() == '|' && ps.left->value.back() == '&') {
//             new_piece = handle_or_and_left(ps);
//             result = result.substr(0, result.length() - ps.value.length()) + new_piece;
//         }

//         ++i;
//     }

//     return result;
// }

// // Проверка корректности CNF
// static bool is_valid(const string& r) noexcept {
//     bool and_zone = true;
//     for (auto it = r.rbegin(); it != r.rend(); ++it) {
//         if (*it == '&' && !and_zone) return false;
//         if (*it != '&') and_zone = false;
//     }
//     return true;
// }

// // Конечная функция CNF
// string conjunctive_normal_form(const string& formula) {
//     string r = negation_normal_form(formula);
//     while (!is_valid(r)) {
//         r = move_and_back(r);
//     }
//     return r;
// }


// #include "../main.hpp"
// #include "../utils/params.hpp"

// using std::string;

// // Проверка оператора
// static bool is_operator(char c) {
//     return c == '&' || c == '|';
// }

// // Рекурсивная функция для перестановок
// static string process(const string& expr) {
//     if (expr.empty()) return "";

//     ParamSet ps = get_params(expr, expr.length() - 1);

//     // ab&c& => abc&&
//     if (ps.value.back() == '&' && ps.left->value.back() == '&') {
//         const string& a = ps.left->left->value;
//         const string& b = ps.left->right->value;
//         const string& c = ps.right->value;
//         return a + b + c + "&&";
//     }
//     // abc&| => ab|ac|b&
//     else if (ps.value.back() == '|' && ps.right->value.back() == '&') {
//         const string& a = ps.left->value;
//         const string& b = ps.right->left->value;
//         const string& c = ps.right->right->value;
//         return a + b + "|" + a + c + "|" + b + "&";
//     }
//     // bc&a| => ab|ac|b&
//     else if (ps.value.back() == '|' && ps.left->value.back() == '&') {
//         const string& a = ps.left->value;
//         const string& b = ps.right->left->value;
//         const string& c = ps.right->right->value;
//         return a + b + "|" + a + c + "|" + b + "&";
//     }

//     // Если ничего не подходит, обрабатываем рекурсивно без изменения
//     string prefix = expr.substr(0, expr.length() - 1);
//     string last_char(1, expr.back());
//     return process(prefix) + last_char;
// }

// // Проверка корректности CNF
// static bool is_valid(const string& r) noexcept {
//     bool and_zone = true;
//     for (auto it = r.rbegin(); it != r.rend(); ++it) {
//         if (*it == '&' && !and_zone) return false;
//         if (*it != '&') and_zone = false;
//     }
//     return true;
// }

// // Главная функция CNF
// string conjunctive_normal_form(const string& formula) {
//     string r = negation_normal_form(formula);
//     while (!is_valid(r)) {
//         r = process(r);
//     }
//     return r;
// }
