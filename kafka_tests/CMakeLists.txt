cmake_minimum_required(VERSION 3.20)
project(kafka_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CLANG_WARNINGS
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
)

set(GCC_WARNINGS
    ${CLANG_WARNINGS}
)

# Set compiler flags to be strict about warnings
if (CMAKE_COMPILER_IS_GNUCXX)
    set(PROJECT_WARNINGS ${GCC_WARNINGS})
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(PROJECT_WARNINGS ${CLANG_WARNINGS})
endif ()

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE ${PROJECT_WARNINGS})

# Tests
## Set up infrastructure
enable_testing()
find_package(Catch2)
find_package(trompeloeil)
add_library(catch_main STATIC test/catch_main.cpp)
target_link_libraries(catch_main PRIVATE Catch2::Catch2 trompeloeil::trompeloeil)

## Add individual test files
find_package(RdKafka)
find_package(fmt)
add_executable(test_kafka test/test_kafka_api.cpp)
target_link_libraries(test_kafka catch_main RdKafka::RdKafka fmt::fmt)
add_test(test_kafka bin/test_kafka)
