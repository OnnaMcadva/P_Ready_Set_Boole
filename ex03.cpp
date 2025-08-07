#include <iostream>
#include <string>
#include <stack>

bool case_operator(char op, bool a, bool b = false) {
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

bool eval_formula(const std::string& formula) {
    std::stack<bool> stack;

    for (char c : formula) {
        if (c == '0') {
            stack.push(false);
        } else if (c == '1') {
            stack.push(true);
        } else if (c == '!') {
            if (stack.empty()) {
                std::cerr << "🤖 Not enough operands for '!'" << std::endl;
                exit(1);
            }
            bool a = stack.top(); stack.pop();
            stack.push(case_operator('!', a));
        } else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=') {
            if (stack.size() < 2) {
                std::cerr << "🤖 Not enough operands for '" << c << "'" << std::endl;
                exit(1);
            }
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(case_operator(c, a, b));
        } else {
            std::cerr << "🤖 Invalid character: '" << c << "'" << std::endl;
            exit(1);
        }
    }

    if (stack.size() != 1) {
        std::cerr << "🤖 Invalid formula: Look into the Stack 👿" << std::endl;
        exit(1);
    }

    return stack.top();
}

// int main() {
//     std::string formulas[] = {
//         "10&",       // false
//         "10|",       // true
//         "11>",       // true
//         "10=",       // false
//         "1011||=",   // true
//         "1!",        // false
//         "10^",       // true
//         "10>!",      // false
//     };

//     for (int i = 0; i < 8; ++i) {
//         std::cout << "Test " << (i + 1) << ": " << formulas[i] << std::endl;
//         bool result = eval_formula(formulas[i]);
//         std::cout << "✨ Result: " << (result ? "true" : "false") << " ✨\n";
//         std::cout << "--------------------------\n";
//     }

//     return 0;
// }