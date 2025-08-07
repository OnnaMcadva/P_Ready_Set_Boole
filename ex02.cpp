#include <iostream>
#include <bitset>

unsigned int BinToGray(unsigned int n) {
    return n ^ (n >> 1);
}

// int main() {
//     for (unsigned int i = 0; i <= 7; ++i) {
//         unsigned int g = BinToGray(i);
//         std::cout << "Gray code (" << i << ") [ " << std::bitset<5>(i) << " ] = " << g
//                   << " [ " << std::bitset<5>(g) << " ]" << std::endl;
//     }
//     return 0;
// }

/* Gray code for a number n is a number where each subsequent code differs from the previous one by only one bit. */
