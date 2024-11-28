add_subdirectory(http)

target_sources(Lattice
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Router.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IRoute.hpp
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Router.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IRoute.cpp
)
