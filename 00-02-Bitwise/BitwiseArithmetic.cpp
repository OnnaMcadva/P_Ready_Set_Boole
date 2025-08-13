#include <iostream>
#include <string>
#include <climits>
#include <cctype>
#include <chrono>
#include <bitset>

unsigned int adder(unsigned int a, unsigned int b) {
    unsigned int sum = a;
    unsigned int carry = b;

    for (int i = 0; i < 32; ++i) {
        unsigned int temp = sum;
        sum = temp ^ carry;
        carry = (temp & carry) << 1;
    }

    return sum;
}

unsigned int multiplier(unsigned int a, unsigned int b) {
    unsigned int product = 0;
    
    for (int i = 0; i < 32; ++i) {
        if (b & 1) {
            product = adder(product, a);
        }
        a <<= 1;
        b >>= 1;
    }
    
    return product;
}

unsigned int BinToGray(unsigned int n) {
    return n ^ (n >> 1);
}

/* 2³² = 4 294 967 296 */

int main() {

    std::cout << "\n💻************ adder ************💻" << std::endl;
    std::pair<unsigned int, unsigned int> testCases[] = {
        {27, 13},
        {123456, 654987},
        {2300000000, 2300000000},
        {0, 0},
        {0, 1000000},
    };

    for (int i = 0; i < 5; ++i) {
        unsigned int a = testCases[i].first;
        unsigned int b = testCases[i].second;

        auto start = std::chrono::high_resolution_clock::now();
        unsigned int sum = adder(a, b);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        std::cout << "\nTest " << (i + 1) << ": a = " << a << ", b = " << b << std::endl;
        std::cout << "✨ Sum: " << sum << " ✨" << std::endl;
        std::cout << "🐉 Time: " << duration.count() << " nanoseconds 🐉" << std::endl;

    }

    unsigned int testA[] = {1000, 9999, 65536, 0, 0};
    unsigned int testB[] = {1234, 9889, 65536, 0, 1000000};

    const int numTests = 5;
    const int iterations = 1000;

    std::cout << "\n💻************ multiplier ************💻" << std::endl;

    for (int i = 0; i < numTests; ++i) {
        unsigned int a = testA[i];
        unsigned int b = testB[i];
        unsigned int result = 0;

        uint64_t totalTime = 0;

        for (int j = 0; j < iterations; ++j) {
            auto start = std::chrono::high_resolution_clock::now();
            result = multiplier(a, b);
            auto end = std::chrono::high_resolution_clock::now();

            totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }

        uint64_t averageTime = totalTime / iterations;

        std::cout << "\nTest " << (i + 1) << ": a = " << a << ", b = " << b << std::endl;
        std::cout << "✨ Product: " << result << " ✨" << std::endl;
        std::cout << "🐉 Average Time: " << averageTime << " nanoseconds 🐉" << std::endl;
    }

    std::cout << "\n💻************ gray_code ************💻" << std::endl;
    for (unsigned int i = 0; i <= 7; ++i) {
        unsigned int g = BinToGray(i);
        std::cout << "Gray code (" << i << ") [ " << std::bitset<5>(i) << " ] = " << g
                  << " [ " << std::bitset<5>(g) << " ]" << std::endl;
    }

    return 0;
}

/* Gray code for a number n is a number where each subsequent 
    code differs from the previous one by only one bit. */