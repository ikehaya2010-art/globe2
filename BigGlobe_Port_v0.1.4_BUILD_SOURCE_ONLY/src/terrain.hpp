#pragma once
#include <cstdint>

namespace bgport {
struct TerrainSettings {
    double baseHeight = 64.0;
    double continentScale = 0.0018;
    double detailScale = 0.012;
    double mountainScale = 0.00075;
    double continentAmplitude = 42.0;
    double detailAmplitude = 7.0;
    double mountainAmplitude = 95.0;
    double seaLevel = 63.0;
};
double sampleHeight(std::uint64_t seed, std::int64_t blockX,
                    std::int64_t blockZ, const TerrainSettings& settings = {});
}
