#include "Logic.hpp"
#include <iostream>

int main() {
    PostfixEvaluator evaluator;
    TruthTableGenerator tableGen;

    std::cout << "\n💻************ Boolean evaluation ************💻\n";

    std::string formulas[] = {
        "10&",
        "10|",
        "11>",
        "10=",
        "10|1&",
        "1011||=",
        "1!",
        "10^",
        "10>!",
    };

    std::string schemes[] {
        "{ ⊤ ∧ ⊥ }",
        "{ ⊤ ∨ ⊥ }",
        "{ ⊤ ⇒ ⊤ }",
        "{ ⊤ ⇔ ⊥ }",
        "{ (T ∨ ⊥) ∧ T) }",
        "{ T ↔ (⊥ ∨ (T ∨ T)) }",
        "{ ¬ ⊤ }",
        "{ ⊤ ⊕ ⊥ }",
        "{ ¬ (⊤ ⇒ ⊥) }",
    };

    for (int i = 0; i < 9; ++i) {
        std::cout << "Test " << (i + 1) << ": " << formulas[i] << std::endl;
        std::cout << "Scheme: " << schemes[i] << std::endl;
        bool result = evaluator.evalFormula(formulas[i]);
        std::cout << "✨ Result: " << (result ? "true" : "false") << " ✨\n";
        std::cout << "--------------------------\n";
    }

    std::cout << "\n💻************ Truth table ************💻\n";
    std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡\n" << "{ AB&C| }\n";
    std::string formula = "AB&C|";
    tableGen.printTruthTable(formula);
    std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡\n" << "{ AB> }\n";
    formula = "AB>";
    tableGen.printTruthTable(formula);
    std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡\n" << "{ AB&A> }\n";
    formula = "AB&A>";
    tableGen.printTruthTable(formula);
    std::cout << "⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡\n" << "\n";
}