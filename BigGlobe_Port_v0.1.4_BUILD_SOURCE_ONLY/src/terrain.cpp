#include "terrain.hpp"
#include "noise.hpp"
#include <algorithm>
#include <cmath>

namespace bgport {
double sampleHeight(std::uint64_t seed, std::int64_t blockX,
                    std::int64_t blockZ, const TerrainSettings& s) {
    const double x = static_cast<double>(blockX);
    const double z = static_cast<double>(blockZ);

    const double continents = fbm2D(seed ^ 0x434F4E54494E454EULL,
        x * s.continentScale, z * s.continentScale, 5, 2.0, 0.5);
    const double detail = fbm2D(seed ^ 0x44455441494CULL,
        x * s.detailScale, z * s.detailScale, 3, 2.1, 0.48);
    const double mountains = std::pow(std::max(0.0,
        fbm2D(seed ^ 0x4D4F554E5441494EULL,
        x * s.mountainScale, z * s.mountainScale, 4, 2.0, 0.52)), 1.7);

    const double height = s.baseHeight
        + continents * s.continentAmplitude
        + detail * s.detailAmplitude
        + mountains * s.mountainAmplitude;
    return std::clamp(height, -512.0, 511.0);
}
}
