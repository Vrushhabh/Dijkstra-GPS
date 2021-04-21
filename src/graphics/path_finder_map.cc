


#include <graphics/path_finder_map.h>
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace pathfinder {
namespace graphics {
PathFinderMap::PathFinderMap(const glm::vec2 &top_left_corner, size_t num_spaces_per_side,
                                       double sketchpad_size, double brush_radius):
                                       top_left_corner_(top_left_corner),
                                       num_spaces_per_side_(num_spaces_per_side),
                                       space_side_length_(sketchpad_size / num_spaces_per_side),
                                       brush_radius_(brush_radius) {
    top_left_corner_ = top_left_corner;
    num_spaces_per_side_  =num_spaces_per_side;
    space_side_length_ = (sketchpad_size / num_spaces_per_side);
    brush_radius_ = brush_radius;
}

void PathFinderMap::DrawMap() {
    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            ci::gl::color(ci::Color::gray(0.3f));

            glm::vec2 pixel_top_left = top_left_corner_ + glm::vec2(col * space_side_length_,
                                                          row * space_side_length_);
            ci::gl::drawSolidCircle(pixel_top_left, 10);
            glm::vec2 pixel_bottom_right =
                    pixel_top_left + cinder::vec2(space_side_length_, space_side_length_);
            ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
            //ci::gl::drawSolidRect(pixel_bounding_box);
            ci::gl::color(ci::Color("black"));
            //ci::gl::drawStrokedRect(pixel_bounding_box);
        }
    }

}

}


}