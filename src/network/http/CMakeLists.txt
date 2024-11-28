target_sources(Lattice
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/HttpServer.hpp
        ${CMAKE_CURRENT_LIST_DIR}/HttpClient.hpp
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/HttpServer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/HttpClient.cpp
)
