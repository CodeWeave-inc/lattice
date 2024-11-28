cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER clang)

project(Lattice
        VERSION 0.1
        DESCRIPTION "A c++ webserver including a router"
        LANGUAGES CXX
)

find_package(spdlog REQUIRED)
find_package(asio REQUIRED)
find_package(cpptrace REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(Lattice)
target_link_libraries(Lattice PUBLIC spdlog::spdlog asio::asio cpptrace::cpptrace nlohmann_json::nlohmann_json)

add_compile_definitions(LATTICE_VERSION="${PROJECT_VERSION}")
add_compile_definitions(HTTP_VERSION="1.0")
add_compile_definitions(CPPTRACE_UNPREFIXED_TRY_CATCH)

add_subdirectory(tests)
add_subdirectory(src)
