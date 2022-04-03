#include <iostream>
#include <vector>

#include "graph.hpp"

template <typename T>
using GraphSetUp = std::pair<std::vector<T>, std::vector<std::pair<T, T>>>;

int main() {

    GraphSetUp<int> set_up{{1, 2, 3, 4, 5, 6, 7, 8}, {
        {1, 2}, {6, 3}, {4, 8},
        {1, 6}, {3, 7}, {1, 5},
        {3, 4}
    }};
    Graph<int> graph;
    graph.InitializeGraph(set_up.first, set_up.second);
    graph.FormAdjacencyList();
    //graph.ShowAdjacencyList(std::cout);

    auto path = graph.GetPath(1, 8, SearchType::DFS);
    std::cout << "BFS: ";
    for (const auto& elem : path) {
        std::cout << elem << " -> ";
    }
    std::cout << "#" << std::endl;

    path = graph.GetPath(1, 8, SearchType::DFS);
    std::cout << "DFS: ";
    for (const auto& elem : path) {
        std::cout << elem << " -> ";
    }
    std::cout << "#" << std::endl;
    return 0;
}