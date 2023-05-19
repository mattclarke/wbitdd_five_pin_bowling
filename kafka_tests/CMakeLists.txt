include(CTest)

find_package(Catch2 REQUIRED)
find_package(fmt REQUIRED)
find_package(RdKafka REQUIRED)
#find_package(LZ4 REQUIRED)

add_executable(kafka_api_test test_kafka_api.cpp)
target_link_libraries(kafka_api_test PRIVATE Catch2::Catch2WithMain fmt::fmt RdKafka::rdkafka++)
target_include_directories(kafka_api_test PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/include $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
add_test(NAME kafka_api_test COMMAND kafka_api_test)