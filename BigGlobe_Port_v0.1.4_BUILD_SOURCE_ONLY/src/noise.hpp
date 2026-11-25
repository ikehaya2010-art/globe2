#pragma once
#include <cstdint>

namespace bgport {
double valueNoise2D(std::uint64_t seed, double x, double z);
double fbm2D(std::uint64_t seed, double x, double z,
             int octaves, double lacunarity, double gain);
}
