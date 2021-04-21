


#include <graphics/path_finder_map.h>
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace pathfinder {
namespace graphics {
PathFinderMap::PathFinderMap(const glm::vec2 &top_left_corner, size_t num_spaces_per_side,
                                       double sketchpad_size, double brush_radius) {
    top_left_corner_ = top_left_corner;
    num_spaces_per_side_  = num_spaces_per_side;
    space_side_length_ = (sketchpad_size / num_spaces_per_side);
    brush_radius_ = brush_radius;
    std::vector<int> pixels(num_spaces_per_side, 0);
    std::vector<std::vector<int>> rows(num_spaces_per_side, pixels);
    image_ = rows;
}

void PathFinderMap::DrawMap() {
    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            //The number is temporary and will be replaced by a enum type
            if (image_[row][col] == 1) {
                ci::gl::color(ci::Color::gray(.2f));
                glm::vec2 pixel_top_left = top_left_corner_ + glm::vec2(col * space_side_length_,
                                                                        row * space_side_length_);
                ci::gl::drawSolidCircle(pixel_top_left, 10);
                ci::gl::color(ci::Color("black"));
                ci::gl::drawStrokedCircle(pixel_top_left, 10);
            } else {
                ci::gl::color(ci::Color::gray(.9f));
                glm::vec2 pixel_top_left = top_left_corner_ + glm::vec2(col * space_side_length_,
                                                                        row * space_side_length_);
                ci::gl::drawSolidCircle(pixel_top_left, 10);
                ci::gl::color(ci::Color("black"));
                ci::gl::drawStrokedCircle(pixel_top_left, 10);
            }
        }
    }
}

void PathFinderMap::BlockBrush(const cinder::vec2& brush_screen_coords) {
    cinder::vec2 brush_sketchpad_coords =
            (brush_screen_coords - top_left_corner_) / (float)space_side_length_;
    //Goes through each space to see if it is where the user clicked to change the state of the space
    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            cinder::vec2 pixel_center = {col + 0.5, row + 0.5};
            if (glm::distance(brush_sketchpad_coords, pixel_center) <=
                brush_radius_) {
                //The number is temporary and will be replaced by a enum type
                image_[row][col] = 1;

            }
        }
    }
}
}
}