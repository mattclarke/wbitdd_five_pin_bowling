cmake_minimum_required(VERSION 3.24)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

project(wbitdd_five_pin_bowling)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wunused -Wconversion")

find_package(RdKafka CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(catch2 CONFIG REQUIRED)

enable_testing()
add_subdirectory(kafka_tests)
