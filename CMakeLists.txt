cmake_minimum_required (VERSION 3.5)
project (GraphAPI)

set(SOURCES 
        ./graph_algo/main.cpp
)

set(HEADERS 
        ./graph_algo/graph.hpp
)

add_executable(graph ${SOURCES} ${HEADERS})
set_target_properties(
    graph PROPERTIES
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)