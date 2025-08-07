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

unsigned int multiplier(unsigned int a, unsigned int b) {
    unsigned int product = 0;
    
    while (b != 0) {
        if (b & 1) {
            product = adder(product, a);
        }
        a <<= 1;
        b >>= 1;
    }
    
    return product;
}

// int main() {

//     unsigned int testA[] = {1000, 9999, 65536, 0, 0};
//     unsigned int testB[] = {1234, 9889, 65536, 0, 1000000};

//     const int numTests = 5;
//     const int iterations = 1000;

//     std::cout << "💻    💻    💻    💻    💻" << std::endl;

//     for (int i = 0; i < numTests; ++i) {
//         unsigned int a = testA[i];
//         unsigned int b = testB[i];
//         unsigned int result = 0;

//         uint64_t totalTime = 0;

//         for (int j = 0; j < iterations; ++j) {
//             auto start = std::chrono::high_resolution_clock::now();
//             result = multiplier(a, b);
//             auto end = std::chrono::high_resolution_clock::now();

//             totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//         }

//         uint64_t averageTime = totalTime / iterations;

//         std::cout << "\nTest " << (i + 1) << ": a = " << a << ", b = " << b << std::endl;
//         std::cout << "✨ Product: " << result << " ✨" << std::endl;
//         std::cout << "🐉 Average Time: " << averageTime << " nanoseconds 🐉" << std::endl;
//         std::cout << "--------------------------\n";
//     }

//     return 0;
// }

/* 2³² = 4 294 967 296 */