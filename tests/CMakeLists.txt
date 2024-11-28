find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests)
set(TEST_TARGET ${PROJECT_NAME}Tests)

add_executable(${TEST_TARGET} main.cpp)

gtest_discover_tests(${TEST_TARGET})
target_link_libraries(${TEST_TARGET}
        PUBLIC
        gtest::gtest
        Lattice
)

add_subdirectory(network)
