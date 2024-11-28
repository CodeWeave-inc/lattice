add_subdirectory(http)

target_sources(Lattice
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/IMessage.hpp
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/IMessage.cpp
)
