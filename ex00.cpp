#include <iostream>
#include <climits>

unsigned int adder(unsigned int a, unsigned int b) {
    if (static_cast<unsigned long long>(a) + b > UINT_MAX) {
        std::cerr << "Error: Sum exceeds UINT_MAX" << std::endl;
        return 0;
    }

    unsigned int sum = a;
    unsigned int carry = b;

    while (carry != 0) {
        unsigned int temp = sum;
        sum = temp ^ carry;
        carry = (temp & carry) << 1;
    }

    return sum;
}

int main() {
    unsigned int test_cases[][2] = {
        {3, 2},
        {7, 8},
        {4294967295, 1},
        {0, 0}
    };

    for (const auto& test : test_cases) {
        unsigned int a = test[0], b = test[1];
        std::cout << "Input: a = " << a << ", b = " << b << "\n";
        std::cout << "Result: " << adder(a, b) << "\n\n";
    }

    return 0;
}
