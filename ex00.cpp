#include <iostream>
#include <string>
#include <climits>
#include <cctype>
#include <chrono>

unsigned int adder(unsigned int a, unsigned int b) {
    unsigned int sum = a;
    unsigned int carry = b;

    while (carry != 0) {
        unsigned int temp = sum;
        sum = temp ^ carry;
        carry = (temp & carry) << 1;
    }

    return sum;
}

// bool is_valid_uint32(const std::string& input) {
//     if (input.empty()) return false;
    
//     for (char c : input) {
//         if (!isdigit(c)) {
//             return false;
//         }
//     }
    
//     try {
//         unsigned long num = std::stoul(input);
//         return num <= UINT_MAX;
//     } catch (...) {
//         return false;
//     }
// }

// int main() {
//     std::string input1, input2;
//     unsigned int a, b;

//     while (true) {
//         std::cout << "Enter first number (0-" << UINT_MAX << "): ";
//         std::getline(std::cin, input1);
        
//         if (!is_valid_uint32(input1)) {
//             std::cerr << "Error❌  Input must contain only digits 0-9\n";
//             continue;
//         }
//         break;
//     }

//     while (true) {
//         std::cout << "Enter second number (0-" << UINT_MAX << "): ";
//         std::getline(std::cin, input2);
        
//         if (!is_valid_uint32(input2)) {
//             std::cerr << "Error❌  Input must contain only digits 0-9\n";
//             continue;
//         }
//         break;
//     }

//     a = std::stoul(input1);
//     b = std::stoul(input2);

//     auto start = std::chrono::high_resolution_clock::now();
//     unsigned int sum = adder(a, b);
//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
//     std::cout << "✨ Sum: " << sum << " ✨" << std::endl;
//     std::cout << "🐉 Time: " << duration.count() << " nanoseconds 🐉" << std::endl;

//     return 0;
// }

/* 2³² = 4 294 967 296 */
