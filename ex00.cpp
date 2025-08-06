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

// int main() {
//     std::pair<unsigned int, unsigned int> testCases[] = {
//         {27, 13},
//         {123456, 654987},
//         {2300000000, 2300000000},
//         {0, 0},
//         {0, 1000000},
//     };

//     for (int i = 0; i < 5; ++i) {
//         unsigned int a = testCases[i].first;
//         unsigned int b = testCases[i].second;

//         auto start = std::chrono::high_resolution_clock::now();
//         unsigned int sum = adder(a, b);
//         auto end = std::chrono::high_resolution_clock::now();

//         auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

//         std::cout << "\nTest " << (i + 1) << ": a = " << a << ", b = " << b << std::endl;
//         std::cout << "✨ Sum: " << sum << " ✨" << std::endl;
//         std::cout << "🐉 Time: " << duration.count() << " nanoseconds 🐉" << std::endl;
//         std::cout << "--------------------------\n" << std::endl;
//     }

//     return 0;
// }

/* 2³² = 4 294 967 296 */
