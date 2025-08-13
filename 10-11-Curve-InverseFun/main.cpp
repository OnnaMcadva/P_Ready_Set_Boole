#include <iostream>
#include <cstdint>
#include <iomanip>
#include <cmath>

static inline uint32_t toMorton2D(uint16_t x, uint16_t y) {
    uint32_t cell = 0;
    for (int i = 0; i < 16; ++i) {
        cell |= (uint32_t)((x >> i) & 1u) << (2*i);
        cell |= (uint32_t)((y >> i) & 1u) << (2*i + 1);
    }
    return cell;
}

double map(uint16_t x, uint16_t y) {
    const double denom = 4294967295.0; // 2^32 - 1
    uint32_t cell = toMorton2D(x, y);
    return cell / denom;
}

static inline void deMorton2D(uint32_t cell, uint16_t &x, uint16_t &y) {
    x = 0; y = 0;
    for (int i = 0; i < 16; ++i) {
        x |= ((cell >> (2*i))     & 1u) << i;
        y |= ((cell >> (2*i + 1)) & 1u) << i;
    }
}

void reverse_map(double val, uint16_t &x, uint16_t &y) {
    const double denom = 4294967295.0;
    if (val < 0.0 || val > 1.0) {
        std::cerr << "Error: value out of range [0, 1]\n";
        return;
    }
    uint32_t cell = (uint32_t)std::llround(val * denom);
    deMorton2D(cell, x, y);
}

int main() {
    std::cout << std::setprecision(17);

    uint16_t tests[][2] = {
        {0,0}, {0,1}, {1,0}, {1,1}, {12345, 54321}, {65535, 65535}
    };
    std::cout << "\n✨ Curve :  ✨" << std::endl;
    std::cout << "✨ (x, y) -> num of cell, map value ✨\n" << std::endl;
    for (auto &p : tests) {
        uint16_t x = p[0], y = p[1];
        uint32_t cell = toMorton2D(x, y);
        double val = map(x, y);
        std::cout << "(" << x << "," << y << ") -> cell = " << cell << ", map = " << val << "\n";

        // uint16_t rx, ry;
        // deMorton2D(cell, rx, ry);
        // if (rx != x || ry != y) {
        //     std::cerr << "Inverse check failed for (" << x << "," << y << ")\n";
        //     return 1;
        // }
    }

    std::cout << "\n✨ Inverse function :  ✨" << std::endl;
    std::cout << "✨ map value -> (x, y)  ✨\n" << std::endl;
    double funcValue[3] = { 0.0625, 0.0000000002328306437, 0.65283294107132428 };

    for (auto &f : funcValue) {
        uint16_t rx, ry;
        reverse_map(f, rx, ry);
        std::cout << "reverse_map -> (" << rx << "," << ry << ")\n";

    }

    return 0;
}
