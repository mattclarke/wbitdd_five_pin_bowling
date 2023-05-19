cmake_minimum_required(VERSION 3.24)
project(wbitdd_five_pin_bowling)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wunused -Wconversion")

#find_package(fmt REQUIRED)
#
#add_library(${PROJECT_NAME} SHARED src/ray.cpp)
#target_include_directories(${PROJECT_NAME} PRIVATE include/)
#
#add_executable(main main.cpp)
#target_include_directories(main PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/include $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
#target_link_libraries(main PRIVATE ${PROJECT_NAME} fmt::fmt)

enable_testing()
add_subdirectory(kafka_tests)
