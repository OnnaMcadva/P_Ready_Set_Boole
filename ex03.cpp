#include <iostream>
#include <string>
#include <stack>

bool case_operator(char op, bool a, bool b = false) {
    switch (op) {
        case '!': return !a;
        case '&': return a && b;
        case '|': return a || b;
        case '^': return a ^ b;
        case '>': return !a || b; // ->
        case '=': return a == b;
        default:
            std::cerr << "👿 Unknown operator: " << op << std::endl;
            exit(1);
    }
}

bool eval_formula(const std::string& formula) {
    std::stack<bool> bool_stack;

    for (char c : formula) {
        if (c == '0') {
            bool_stack.push(false);
        } else if (c == '1') {
            bool_stack.push(true);
        } else if (c == '!') {
            if (bool_stack.empty()) {
                std::cerr << "🤖 Not enough operands for '!' 🐬" << std::endl;
                exit(1);
            }
            bool a = bool_stack.top(); bool_stack.pop();
            bool_stack.push(case_operator('!', a));
        } else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=') {
            if (bool_stack.size() < 2) {
                std::cerr << "🤖 Not enough operands for '" << c << "' 🐬" << std::endl;
                exit(1);
            }
            bool b = bool_stack.top(); bool_stack.pop();
            bool a = bool_stack.top(); bool_stack.pop();
            bool_stack.push(case_operator(c, a, b));
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

// int main() {
//     std::string formulas[] = {
//         "10&",
//         "10|",
//         "11>",
//         "10=",
//         "10|1&",
//         "1011||=",
//         "1!",
//         "10^",
//         "10>!",
//         "01!",
//     };

//     std::string schemes[] {
//         "{ ⊤ ∧ ⊥ }",
//         "{ ⊤ ∨ ⊥ }",
//         "{ ⊤ ⇒ ⊤ }",
//         "{ ⊤ ⇔ ⊥ }",
//         "{ (T ∨ ⊥) ∧ T) }",
//         "{ T ↔ (⊥ ∨ (T ∨ T)) }",
//         "{ ¬ ⊤ }",
//         "{ ⊤ ⊕ ⊥ }",
//         "{ ¬ (⊤ ⇒ ⊥) }",
//         "~",
//     };

//     for (int i = 0; i < 10; ++i) {
//         std::cout << "Test " << (i + 1) << ": " << formulas[i] << std::endl;
//         std::cout << "Scheme: " << schemes[i] << std::endl;
//         bool result = eval_formula(formulas[i]);
//         std::cout << "✨ Result: " << (result ? "true" : "false") << " ✨\n";
//         std::cout << "--------------------------\n";
//     }

//     return 0;
// }