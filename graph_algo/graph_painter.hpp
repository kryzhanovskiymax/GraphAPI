#pragma once

#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "svg/svg.hpp"

namespace graph {

namespace domain {

    struct Size {
        int height;
        int width;
        int padding;
    };  

    struct GraphRepresentationConfig {
        int stroke_width = 2;
        int vertice_radius = 7;
        int mst_line_width = 3;
        std::vector<svg::Color> palette = {svg::Rgb(45, 45, 60)};
        std::vector<svg::Color> vertice_palette = {svg::Rgb(60, 80, 80)};
        std::vector<svg::Color> edge_palette = {svg::Rgb(100, 100, 100)};
        svg::Color mst_color = svg::Rgb(150, 10, 10);
        svg::Color mst_vertice = svg::Rgb(150, 10, 10);
    };

    struct RepresentationFlags {
        bool highlight_mst = false;
        bool heighlight_path = false;
    };

}

class GraphPainter {
public:

    GraphPainter() {};
    GraphPainter(domain::Size size, domain::GraphRepresentationConfig config, domain::RepresentationFlags flags):
                    image_size(size), representation_config(config), representation_flags(flags) {}

    void InitializeGraphPainter(Graph<std::string> graph_, Graph<std::string> mst_) {
        this->graph = graph_;
        this->mst = mst_;
    }

    void InitializeGraphPainter(Graph<std::string> graph_) {
        this->graph = graph_;
    }

    void RenderGraph(std::ostream& os) {

    }
    
    GraphPainter& SetStrokeWidth (int width) {
        representation_config.stroke_width = width;
        return *this;
    }

    GraphPainter& SetVerticeRadius (int radius) {
        representation_config.vertice_radius = radius;
        return *this;
    }

    GraphPainter& SetMSTLineWidth (int width) {
        representation_config.mst_line_width = width;
        return *this;
    }

    GraphPainter& SetVerticePalette (std::vector<svg::Color> colors) {
        representation_config.vertice_palette = colors;
        return *this;
    }

    GraphPainter& SetEdgePalette (std::vector<svg::Color> colors) {
        representation_config.edge_palette = colors;
        return *this;
    }

    GraphPainter& SetMSTEdgeColor (svg::Color color) {
        representation_config.mst_color = color;
        return *this;
    }

    GraphPainter& SetMST(Graph<std::string> mst_) {
        this->mst = mst_;
        return *this;
    }

    GraphPainter& SetGraph(Graph<std::string> graph_) {
        graph = graph_;
        return *this;
    } 

    GraphPainter& SetMSTHighlight(bool mst_highlight) {
        representation_flags.highlight_mst = mst_highlight;
        return *this;
    } 

    GraphPainter& SetSize(int width, int height, int padding) {
        image_size.width = width;
        image_size.height = height;
        image_size.padding = padding;
        return *this;
    }

    std::vector<svg::Point> GetPositions(int num) {
        return GeneratePositions(num);
    } 

private:
    domain::Size image_size;
    domain::GraphRepresentationConfig representation_config;
    domain::RepresentationFlags representation_flags;
    std::unordered_map<std::string, svg::Point> vertices_to_positions;
    Graph<std::string> graph;
    Graph<std::string> mst;

    std::vector<svg::Point> GeneratePositions(int num_of_positions) {
        srand(time(NULL));
        int gap_between_rows = representation_config.vertice_radius;
        int gap_between_vertices = representation_config.vertice_radius;

        int pixel_width = 2 * (representation_config.vertice_radius + gap_between_vertices);
        int pixel_height = 2 * (representation_config.vertice_radius + gap_between_rows);
        int elements_per_row = (image_size.width - image_size.padding * 2) / pixel_width;
        int elements_per_column = (image_size.height - image_size.padding * 2) / pixel_height;

        std::set<svg::Point> positions;

        while(positions.size() < num_of_positions) {
            svg::Point pos;
            pos.x = image_size.padding + (rand() % elements_per_row) * pixel_width 
                    + gap_between_rows + representation_config.vertice_radius;
            pos.y = image_size.padding + (rand() % elements_per_row) * pixel_height 
                    + gap_between_rows + representation_config.vertice_radius;

            positions.insert(pos);
        }

        return {positions.begin(), positions.end()};
    }

    void DrawGraphRepresentation(svg::Document& image) {
        DrawVertices(image);
        DrawVerticesNames(image);
        DrawGraphEdges(image);

        if (representation_flags.highlight_mst) {
            DrawMSTEdges(image);
            DrawMSTVertices(image);
        }
    }

    void DrawVertices(svg::Document& image) {
        
    }

    void DrawVerticesNames(svg::Document& image);
    void DrawGraphEdges(svg::Document& image);
    void DrawMSTVertices(svg::Document& image);
    void DrawMSTEdges(svg::Document& image);
};

}