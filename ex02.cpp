#include <iostream>
#include <bitset>

unsigned int BinToGray(unsigned int n) {
    return n ^ (n >> 1);
}

// int main() {
//     for (unsigned int i = 0; i <= 12; ++i) {
//         unsigned int g = BinToGray(i);
//         std::cout << "Gray code(" << i << ") = " << g
//                   << " (" << std::bitset<4>(g) << ")" << std::endl;
//     }
//     return 0;
// }
