#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

/*#include "graph.hpp"

template <typename T>
using GraphSetUp = std::pair<std::vector<T>, std::vector<std::pair<T, T>>>;*/

template <typename T>
class ConnectedComponents {
public:
    ConnectedComponents(std::initializer_list<T> vertices) {
        int i = 0;
        for (auto iter = vertices.begin(); iter != vertices.end(); ++iter) {
            components[i].push_back(*iter);
            vertice_to_component[*iter] = i;
            ++i;
        }

        available_id = vertices.size();
    }

    ConnectedComponents(const std::vector<T>& vertices) {
        int i = 0;
        for (int i = 0; i < vertices.size(); ++i) {
            components[i].push(vertices[i]);
            vertice_to_component[vertices[i]] = i;
        }

        available_id = vertices.size();
    }

    void LinkVertices(const T& v1, const T& v2) {
        if (vertice_to_component.count(v1) > 0 && vertice_to_component.count(v2) > 0) {
            MergeComponents(vertice_to_component.at(v1), vertice_to_component.at(v2));
        } else if (vertice_to_component.count(v1) > 0 && vertice_to_component.count(v2) == 0) {
            vertice_to_component[v2] = vertice_to_component[v1];
            components[vertice_to_component[v1]].push_back(v2);
        } else if (vertice_to_component.count(v1) == 0 && vertice_to_component.count(v2) > 0) {
            vertice_to_component[v1] = vertice_to_component[v2];
            components[vertice_to_component[v2]].push_back(v2);
        } else {
            components[available_id].push_back(v1);
            vertice_to_component[v1] = available_id;
            ++available_id;

            components[available_id].push_back(v2);
            vertice_to_component[v2] = available_id;
        }
    }

    bool InSameComponent(const T& v1, const T& v2) {
        return vertice_to_component[v1] == vertice_to_component[v2];
    }

    void ShowComponents() {
        for (const auto& component : components) {
            std::cout << "{ ";
            for (const auto& vertice : component.second) {
                std::cout << vertice << " ";
            }
            std::cout << "}" << std::endl;
        }
    }

private:
    int available_id = 0;
    std::unordered_map<int, std::list<T>> components;
    std::unordered_map<T, int> vertice_to_component;

    void MergeComponents(int first_id, int second_id) {
        //std::cout << "started merging" << std::endl;
        while(!components[second_id].empty()) {

            T temp = components[second_id].back();
            //std::cout << "pushing " << temp << ", back: " << components[second_id].back() << std::endl;
            components[second_id].pop_back();
            components[first_id].push_back(temp);
            vertice_to_component[temp] = first_id;
        }
    
        components.erase(second_id);
    }

};




int main() {

    /*GraphSetUp<int> set_up{{1, 2, 3, 4, 5, 6, 7, 8}, {
        {1, 2}, {6, 3}, {4, 8},
        {1, 6}, {3, 7}, {1, 5},
        {3, 4}
    }};
    GraphProcess<int> graph;
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
    std::cout << "#" << std::endl;*/
    ConnectedComponents components({1, 2, 3, 4, 5, 6});
    components.LinkVertices(1, 2);
    components.LinkVertices(5, 6);
    components.LinkVertices(4, 6);
    components.LinkVertices(2, 5);
    components.ShowComponents();
    std::cout << "----" << std::endl;
    components.LinkVertices(3, 7);
    components.LinkVertices(8, 9);
    components.ShowComponents();
    std::cout << "---" << std::endl;

    std::cout << components.InSameComponent(1, 2) << std::endl;
    std::cout << components.InSameComponent(3, 1) << std::endl;
    return 0;
}