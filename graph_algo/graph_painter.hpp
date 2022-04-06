#pragma once

#include "svg/svg.hpp"

namespace graph {

namespace domain {

    struct Size {
        int height;
        int width;
    };  

    struct GraphRepresentationConfig {
        int stroke_width;
        int vertice_radius;
        std::vector<svg::Color> palette;
        std::vector<svg::Color> vertice_palette;
        std::vector<svg::Color> edge_palette;
        svg::Color mst_color;
        int mst_line_width;
    };

    struct RepresentationFlags {
        bool highlight_mst = false;
        bool heighlight_path = false;
    }

}

class GraphPainter {
public:

private:
    domain::Size image_size;
    domain::GraphRepresentationConfig representation_config;
    domain::RepresentationFlag representation_flag;
};

}