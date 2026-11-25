#include "noise.hpp"
#include <cmath>
#include <cstdint>

namespace bgport {
namespace {
std::uint64_t mix64(std::uint64_t x) {
    x += 0x9E3779B97F4A7C15ULL;
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
    return x ^ (x >> 31);
}
double lattice(std::uint64_t seed, std::int64_t x, std::int64_t z) {
    const auto a = mix64(seed ^ mix64(static_cast<std::uint64_t>(x)));
    const auto b = mix64(a ^ mix64(static_cast<std::uint64_t>(z)));
    // Map the upper 53 bits to [-1, 1].
    constexpr double scale = 1.0 / 9007199254740991.0;
    return (static_cast<double>(b >> 11) * scale) * 2.0 - 1.0;
}
double fade(double t) { return t * t * (3.0 - 2.0 * t); }
double lerp(double a, double b, double t) { return a + (b - a) * t; }
}
double valueNoise2D(std::uint64_t seed, double x, double z) {
    const auto x0 = static_cast<std::int64_t>(std::floor(x));
    const auto z0 = static_cast<std::int64_t>(std::floor(z));
    const double tx = fade(x - static_cast<double>(x0));
    const double tz = fade(z - static_cast<double>(z0));
    const double a = lerp(lattice(seed, x0, z0), lattice(seed, x0 + 1, z0), tx);
    const double b = lerp(lattice(seed, x0, z0 + 1), lattice(seed, x0 + 1, z0 + 1), tx);
    return lerp(a, b, tz);
}
double fbm2D(std::uint64_t seed, double x, double z, int octaves,
             double lacunarity, double gain) {
    if (octaves <= 0) return 0.0;
    double sum = 0.0, amplitude = 1.0, frequency = 1.0, norm = 0.0;
    for (int i = 0; i < octaves; ++i) {
        sum += valueNoise2D(mix64(seed + static_cast<std::uint64_t>(i)), x * frequency, z * frequency) * amplitude;
        norm += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }
    return norm > 0.0 ? sum / norm : 0.0;
}
}
