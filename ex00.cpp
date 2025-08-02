#include <iostream>

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

int main() {

    unsigned int a = 3, b = 2;
    std::cout << "Input: a = " << a << ", b = " << b << "\n";
    std::cout << "Result: " << adder(a, b) << "\n";

    a = 7, b = 8;
    std::cout << "Input: a = " << a << ", b = " << b << "\n";
    std::cout << "Result: " << adder(a, b) << "\n";

    return 0;
}
