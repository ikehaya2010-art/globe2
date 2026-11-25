#include "noise.hpp"
#include "terrain.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>

int main() {
    const auto a = bgport::sampleHeight(123456789ULL, 100, -250);
    const auto b = bgport::sampleHeight(123456789ULL, 100, -250);
    const auto c = bgport::sampleHeight(123456789ULL, 101, -250);
    assert(a == b);                 // same seed and coordinates => same result
    assert(std::isfinite(a));
    assert(a >= -512.0 && a <= 511.0);
    assert(std::isfinite(c));
    assert(bgport::fbm2D(1, 0.5, 0.5, 0, 2.0, 0.5) == 0.0);
}
