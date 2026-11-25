#include "terrain.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 6) {
        std::cerr << "Usage: terrain_preview <seed> <startX> <startZ> <width> <height>\n";
        return 2;
    }
    const auto seed = static_cast<std::uint64_t>(std::strtoull(argv[1], nullptr, 10));
    const auto startX = std::strtoll(argv[2], nullptr, 10);
    const auto startZ = std::strtoll(argv[3], nullptr, 10);
    const int width = std::atoi(argv[4]);
    const int height = std::atoi(argv[5]);
    if (width < 1 || height < 1 || width > 4096 || height > 4096) {
        std::cerr << "width/height must be 1..4096\n";
        return 2;
    }
    std::cout << "z/x";
    for (int x = 0; x < width; ++x) std::cout << ',' << (startX + x);
    std::cout << '\n' << std::setprecision(2) << std::fixed;
    for (int z = 0; z < height; ++z) {
        std::cout << (startZ + z);
        for (int x = 0; x < width; ++x)
            std::cout << ',' << bgport::sampleHeight(seed, startX + x, startZ + z);
        std::cout << '\n';
    }
}
