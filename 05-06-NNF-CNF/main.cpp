#include "Logic.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "\n💻************ NNF ************💻\n";
        std::cout << toNNF("AB&!") << "\n";    // A!B!|
        std::cout << toNNF("AB|!") << "\n";    // A!B!&
        std::cout << toNNF("AB>") << "\n";     // A!B|
        std::cout << toNNF("AB=") << "\n";     // AB&A!B!&|
        std::cout << toNNF("A!!!") << "\n";     // A!
        std::cout << toNNF("AB|C&!") << "\n";  // A!B!&C!|
        std::cout << toNNF("AB&C|!") << "\n";  // A!B!|C!&

        std::cout << "\n💻************ CNF ************💻\n";
        std::cout << toCNF("AB&!") << "\n";    // A!B!|
        std::cout << toCNF("AB|!") << "\n";    // A!B!&
        std::cout << toCNF("AB|C&") << "\n";     // AB|C&
        std::cout << toCNF("AB|C|D|") << "\n";     // AB|C|D|
        std::cout << toCNF("AB&C&D&") << "\n";     // ABCD&&&
        std::cout << toCNF("AB&!C!|") << "\n";  // A!B!|C!|
        std::cout << toCNF("AB|!C!&") << "\n";  // A!B!C!&&
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

