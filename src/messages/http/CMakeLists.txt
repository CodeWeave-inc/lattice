add_subdirectory(errors)

target_sources(Lattice
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/AbstractHttpMessage.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Header.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Request.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Response.hpp
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AbstractHttpMessage.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Header.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Request.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Response.cpp
)
