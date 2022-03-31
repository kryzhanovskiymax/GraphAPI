#include <vector>
#include <deque>
#include <utility>
#include <map>
#include <unordered_map>
#include <list>

enum class Color {
    White,
    Gray,
    Black
};

template <typename T, typename WeightFunc>
class Graph {
public:

    //void InitializeGraph() {}
    //void InitializeGraph(const std::vector<T>& vertixes, const std::vector<std::pair<T, T>>& edges);
    //void InitializeGraph(const std::vertixes<T>& vertixes, 
    //        const std::vector<std::pair<T, T>>& edges, std::function<double(std::pair<T, T>)> weight);


private:
    struct VertixWrapper {
        T vertix;
        Color color;
        VertixWrapper* parent = nullptr;
    };

    std::deque<VertixWrapper> v_wrappers_;
    std::unordered_map<T, std::list<VertixWrapper*>> adjacency_list_;
    
};