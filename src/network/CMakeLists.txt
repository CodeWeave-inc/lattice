add_subdirectory(http)

target_sources(Lattice
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Server.hpp
        ${CMAKE_CURRENT_LIST_DIR}/AClient.hpp
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Server.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AClient.cpp
)
