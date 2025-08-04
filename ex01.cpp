#include <iostream>
#include <string>
#include <climits>
#include <cctype>

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

