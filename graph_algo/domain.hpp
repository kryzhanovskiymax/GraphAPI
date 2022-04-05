#pragma once

#include <deque>
#include <utility>
#include <memory>

enum class Color {
    White,
    Gray,
    Black
};

enum class SearchType {
    BFS,
    DFS
};

enum class MSTAlgorithm {
    Prim,
    Kruskal
};

template <typename T>
struct Graph {
    std::deque<T> vertices = {};
    std::deque<std::pair<T, T>> edges = {};
    std::function<double(std::pair<T, T>)> weight = [] (const std::pair<T, T>& edge) {
        return 0;
    } ;
};

template <typename T>
struct VertixWrapper {
    T vertix;
    int distance;
    Color color = Color::White;
    std::shared_ptr<VertixWrapper<T>> parent = nullptr;
};