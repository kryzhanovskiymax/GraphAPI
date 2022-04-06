#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

#include "graph.hpp"
#include "graph_reader.hpp"

using namespace graph;

/*template <typename T>
using GraphSetUp = std::pair<std::vector<T>, std::vector<std::pair<T, T>>>;

template <typename T>
void ShowGraphRepresentation(std::ostream& os, const Graph<T>& g) {
    std::cout << "{ ";
    for (const auto& v : g.vertices) {
        std::cout << v << ", ";
    }
    std::cout << "}" << std::endl;

    for (const auto& edge : g.edges) {
        std::cout << "{ " << edge.first << " - " << edge.second << " }" << std::endl;
    }
}*/



int main() {


   /* GraphSetUp<std::string> set_up({"a", "b", "c"}, {{"a", "b"}, {"b", "c"}, {"c", "a"}});
    std::function<double(std::pair<std::string, std::string>)> w = [] (const std::pair<std::string, std::string> edge) {
        if (edge == std::pair<std::string, std::string>({"a", "b"})) {
            return 1;
        } else if (edge == std::pair<std::string, std::string>({"b", "c"})) {
            return 2;
        } else if (edge == std::pair<std::string, std::string>({"c", "a"})) {
            return 3;
        } else {
            return 0;
        }
    };

    GraphProcess<std::string> graph;
    graph.InitializeGraph(set_up.first, set_up.second);
    graph.AddWeightFunction({set_up.second.begin(), set_up.second.end()}, {1, 2, 3});
    graph.FormAdjacencyList();
    auto mst = graph.GenerateMST();
    ShowGraphRepresentation(std::cout, mst);*/

    

    return 0;
}