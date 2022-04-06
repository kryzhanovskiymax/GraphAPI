#pragma once


#include "domain.hpp"

#include <vector>
#include <deque>
#include <utility>
#include <map>
#include <unordered_map>
#include <list>
#include <initializer_list>
#include <functional>
#include <memory>
#include <set>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <algorithm>


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
            components[i].push_back(vertices[i]);
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

template <typename T>
class GraphProcess {
public:

    GraphProcess() {}

    void AddWeightFunction(std::function<double(std::pair<T, T>)> get_weight) {
        graph_representation_.weight(get_weight);
    }

    void InitializeGraph(std::initializer_list<T> vertices, 
            std::initializer_list<std::pair<T, T>> edges) {
        for (const auto& v : vertices) {
            graph_representation_.vertices.push_back(v);
        }

        for (const auto& e : edges) {
            graph_representation_.edges.push_back(e);
        }
    }

    void InitializeGraph(const std::vector<T>& vertices, 
            const std::vector<std::pair<T, T>>& edges) {
        for (const auto& v : vertices) {
            graph_representation_.vertices.push_back(v);
        }

        for (const auto& e : edges) {
            graph_representation_.edges.push_back(e);
        }
    }

    void InitializeGraph(std::initializer_list<T> vertices, 
            std::initializer_list<std::pair<T, T>> edges, std::function<double(std::pair<T, T>)> get_weight)  {
        InitializeGraph(vertices, edges);
        AddWeight(get_weight);
    }

    std::vector<T> GetPath(T source, T target, SearchType type = SearchType::BFS) {
        if (type == SearchType::BFS) {
            return GetPathBFS(source, target);
        } else {
            return GetPathDFS(source, target);
        }
    }

    std::ostream& ShowAdjacencyList(std::ostream& os) {
        for (const auto& [v, connections] : adjacency_list_) {
            os << v << " -> ";
            for (auto elem : connections) {
                os << elem->vertix << " -> ";
            }
            os << "#" << std::endl;
        }

        return os;
    }

    void FormAdjacencyList() {

        for (const auto& v : graph_representation_.vertices) {
            adjacency_list_.insert({v, {}});
        }

        for (const auto& [left, right] : graph_representation_.edges) {
            if (vertices_to_wrappers.count(left) < 1) {
                vertices_to_wrappers.insert({left, std::make_shared<VertixWrapper<T>>(VertixWrapper<T>{left, INT_MAX, Color::White, nullptr})});
            }

            if (vertices_to_wrappers.count(right) < 1) {
                vertices_to_wrappers.insert({right, std::make_shared<VertixWrapper<T>>(VertixWrapper<T>{right, INT_MAX, Color::White, nullptr})});
            }

            adjacency_list_[left].push_back(vertices_to_wrappers.at(right));
            adjacency_list_[right].push_back(vertices_to_wrappers.at(left));
        }

        adjacency_list_formed = true;
    }

    Graph<T> GenerateMST(MSTAlgorithm type = MSTAlgorithm::Kruskal);
private:

    Graph<T> graph_representation_;

    std::unordered_map<T, std::shared_ptr<VertixWrapper<T>>> vertices_to_wrappers;
    std::unordered_map<T, std::list<std::shared_ptr<VertixWrapper<T>>>> adjacency_list_ = {};
    bool adjacency_list_formed = false;

    std::vector<int> FormPath(T target) {
        std::vector<T> path = {};

        auto target_ptr = vertices_to_wrappers.at(target);
        while (target_ptr->parent != nullptr) {
            path.push_back(target_ptr->vertix);
            target_ptr = target_ptr->parent;
        }
        path.push_back(target_ptr->vertix);
        std::reverse(path.begin(), path.end());

        return path;
    }

    void ClearMarks() {
        for (const auto& [v, wrapper] : vertices_to_wrappers) {
            wrapper->color = Color::White;
            wrapper->distance = INT_MAX;
            wrapper->parent = nullptr;
        }
    }

    std::vector<T> GetPathBFS(T source, T target) {
        if (vertices_to_wrappers.count(source) == 0 || vertices_to_wrappers.count(target) == 0) {
            return {};
        }

        if (!adjacency_list_formed) {
            FormAdjacencyList();
        }
        //Clearing graph from previous usages
        ClearMarks();

        std::shared_ptr<VertixWrapper<T>> source_ptr = vertices_to_wrappers.at(source);
        source_ptr->color = Color::Gray;
        source_ptr->distance = 0;

        std::queue<std::shared_ptr<VertixWrapper<T>>> q;
        q.push(source_ptr);

        while(!q.empty()) {
            auto u = q.front();
            q.pop();
            for (const auto& vptr : adjacency_list_[u->vertix]) {
                if (vptr->color == Color::White) {
                    vptr->color = Color::Gray;
                    vptr->distance = u->distance + 1;
                    vptr->parent = u;
                    q.push(vptr);
                }
            }
            u->color = Color::Black;
        }

        return FormPath(target);
    }

    void DFSVisit(std::shared_ptr<VertixWrapper<T>> uptr) {
        uptr->color = Color::Gray;
        for (const auto& vptr : adjacency_list_.at(uptr->vertix)) {
            if (vptr->color == Color::White) {
                vptr->parent = uptr;
                DFSVisit(vptr);
            }
        }
        uptr->color = Color::Black;
    }

    std::vector<T> GetPathDFS(T source, T target) {
        if (vertices_to_wrappers.count(source) == 0 || vertices_to_wrappers.count(target) == 0) {
            return {};
        }

        if (!adjacency_list_formed) {
            FormAdjacencyList();
        }

        //Clearing Graph from previous usages
        ClearMarks();

        auto source_ptr = vertices_to_wrappers.at(source);
        DFSVisit(source_ptr);

        return FormPath(target);
    }

    Graph<T> GenerateMSTKruskal() {
        Graph<T> mst;
        mst.vertices = {graph_representation_.vertices};
        mst.edges = {};

        std::vector<std::pair<T, T>> sorted_edges{graph_representation_.edges.begin(), 
                                                    graph_representation_.edges.end()};
        
        std::sort(sorted_edges.begin(), sorted_edges.end(), [&] (const auto& lhs, const auto& rhs) {
            return graph_representation_.weight(lhs) < graph_representation_.weight(rhs);
        });

        //ConnectedComponents()


        return mst;
    }

    Graph<T> GenerateMSTPrim();
};
