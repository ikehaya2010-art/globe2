cmake_minimum_required(VERSION 3.20)
project(BigGlobeLeviLaminaPort VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(bigglobe_terrain_core
    src/noise.cpp
    src/terrain.cpp
)
target_include_directories(bigglobe_terrain_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(terrain_preview src/main.cpp)
target_link_libraries(terrain_preview PRIVATE bigglobe_terrain_core)

enable_testing()
add_executable(core_tests tests/core_tests.cpp)
target_link_libraries(core_tests PRIVATE bigglobe_terrain_core)
add_test(NAME core_tests COMMAND core_tests)
