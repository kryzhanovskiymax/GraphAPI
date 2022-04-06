#pragma once

#include <unordered_map>
#include <vector>

#include "svg/svg.hpp"

namespace graph {

namespace domain {

    struct Size {
        int height;
        int width;
    };  

    struct GraphRepresentationConfig {
        int stroke_width = 1;
        int vertice_radius = 3;
        std::vector<svg::Color> palette = {svg::Rgb(45, 45, 60)};
        std::vector<svg::Color> vertice_palette = {svg::Rgb(60, 80, 80)};
        std::vector<svg::Color> edge_palette = {svg::Rgb(100, 100, 100)};
        svg::Color mst_color = svg::Rgb(150, 10, 10);
        int mst_line_width = 2;
    };

    struct RepresentationFlags {
        bool highlight_mst = false;
        bool heighlight_path = false;
    }

}

class GraphPainter {
public:

    GraphPainter() {};
    GraphPainter(Size size, GraphRepresentationConfig config, RepresentationFlags flags):
                    image_size(size), representation_config(config), representation_flags(flags) {}
    
    GraphPainter& SetStrokeWidth(int width) {
        representation_config.stroke_width = width;
        return *this;
    }

    GraphPainter& SetVerticeRadius(int radius) {
        representation_config.vertice_radius = radius;
        return *this;
    }

    GraphPainter& SetMSTLineWidth(int width) {
        representation_config.mst_line_width = width;
        return *this;
    }

private:
    domain::Size image_size;
    domain::GraphRepresentationConfig representation_config;
    domain::RepresentationFlag representation_flags;
    std::unordered_map<std::string, svg::Point> vertices_to_positions;


};

}