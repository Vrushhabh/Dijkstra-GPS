


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
    std::vector<SpaceState> pixels(num_spaces_per_side, SpaceState::Normal);
    std::vector<std::vector<SpaceState>> rows(num_spaces_per_side, pixels);
    image_ = rows;
}

void PathFinderMap::DrawMap() {
    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            //The number is temporary and will be replaced by a enum type
            if (image_[row][col] == SpaceState::Blocked) {
                ci::gl::color(ci::Color::gray(.1f));
            } else if (image_[row][col] == SpaceState::Weighted){
                ci::gl::color(ci::Color("purple"));
            } else if (image_[row][col] == SpaceState::Normal){
                ci::gl::color(ci::Color::gray(.9f));
            } else if (image_[row][col] == SpaceState::InShortestPath){
                ci::gl::color(ci::Color("green"));
            }


            glm::vec2 pixel_top_left = top_left_corner_ + glm::vec2(col * space_side_length_,
                                                                    row * space_side_length_);
            ci::gl::drawSolidCircle(pixel_top_left, 10);
            ci::gl::color(ci::Color("black"));
            ci::gl::drawStrokedCircle(pixel_top_left, 10);
        }
    }

    //Distinguishes start space by coloring it blue
    glm::vec2 start_space_position = top_left_corner_ + glm::vec2(0 * space_side_length_, 0 * space_side_length_);
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(start_space_position, 8);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedCircle(start_space_position, 12);


    //Distinguishes start space by coloring it blue
    glm::vec2 end_space_position = top_left_corner_ + glm::vec2((num_spaces_per_side_ - 1) * space_side_length_,
                                                            (num_spaces_per_side_ - 1) * space_side_length_);
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(end_space_position, 8);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedCircle(end_space_position, 12);
}

void PathFinderMap::BlockAdder(const cinder::vec2& brush_screen_coords) {
    cinder::vec2 brush_sketchpad_coords =
            (brush_screen_coords - top_left_corner_) / (float)space_side_length_;
    //Goes through each space to see if it is where the user clicked to change the state of the space
    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            cinder::vec2 pixel_center = {col + 0.5, row + 0.5};
            if (glm::distance(brush_sketchpad_coords, pixel_center) <=
                brush_radius_) {
                //The number is temporary and will be replaced by a enum type
                image_[row][col] = SpaceState::Blocked;
            }
        }
    }
}


void PathFinderMap::FindShortestPath(Map map) {
    map.FindShortestPath(
            0, num_spaces_per_side_ * num_spaces_per_side_ - 1);
    //We start from the larger ints to smaller because the hashmap that originates from the
    //map class has a map where the end destination eventually points to the start point
    bool break_check = false;
    for (int space = map.GetShortestPath().size() - 1; space >= 0; --space) {
        int counter = 0;
        for (size_t row = 0; row < num_spaces_per_side_; row++) {
            for (size_t col = 0; col < num_spaces_per_side_; col++) {
                if (counter == map.GetShortestPath()[space]) {
                    image_[row][col] = SpaceState::InShortestPath;
                    break_check = true;
                    //std::cout<< "in";
                    break;
                }
                counter++;
            }
            if(break_check) {
                //std::cout<< "in2";
                break_check = false;
                break;
            }

        }


    }

}
}

void graphics::PathFinderMap::Clear() {
    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            cinder::vec2 pixel_center = {col + 0.5, row + 0.5};
            image_[row][col] = SpaceState::Normal;
        }
    }
}

void graphics::PathFinderMap::WeightAdder(const glm::vec2 &brush_screen_coords) {
    cinder::vec2 brush_sketchpad_coords =
            (brush_screen_coords - top_left_corner_) / static_cast<float>(space_side_length_);

    for (size_t row = 0; row < num_spaces_per_side_; ++row) {
        for (size_t col = 0; col < num_spaces_per_side_; ++col) {
            cinder::vec2 pixel_center = {col + 0.5, row + 0.5};

            if (glm::distance(brush_sketchpad_coords, pixel_center) <=
                brush_radius_) {
                image_[row][col] = SpaceState::Weighted;
            }
        }
    }

}

Map graphics::PathFinderMap::MakeMap() {
    int normal_connection = 1;
    int weighted_connection = 3;
    int node_num = 0;
    Map map = Map();

    for (size_t row = 0; row < num_spaces_per_side_; row++) {
        for (size_t col = 0; col < num_spaces_per_side_; col++) {
            //Makes normal spaces and there connections with surrounding spaces
            //depending on if the surrounding spaces are weighted spaces or not
               if (image_[row][col] == SpaceState::Weighted) {
                    map.AddSpace(Space(node_num));
                    if (row > 0) {
                        if (image_[row - 1][col] != SpaceState::Blocked) {
                            map.AddConnection(weighted_connection, node_num, node_num - num_spaces_per_side_);
                        }
                    }
                    if (row < num_spaces_per_side_ - 1) {
                        if (image_[row + 1][col] != SpaceState::Blocked) {
                            map.AddConnection(weighted_connection, node_num, node_num + num_spaces_per_side_);
                        }
                    }
                    if (col > 0) {
                        if (image_[row][col - 1] != SpaceState::Blocked) {
                            map.AddConnection(weighted_connection, node_num, node_num - 1);
                        }
                    }
                    if (col < num_spaces_per_side_- 1) {
                        if (image_[row][col + 1] != SpaceState::Blocked) {
                            map.AddConnection(weighted_connection, node_num, node_num + 1);
                        }
                    }
                } else if (image_[row][col] == SpaceState::Normal) {
                map.AddSpace(Space(node_num));
                if (row > 0) {
                    if (image_[row - 1][col] == SpaceState::Normal) {
                        map.AddConnection(normal_connection, node_num, node_num - num_spaces_per_side_);
                    } else if (image_[row - 1][col] == SpaceState::Weighted) {
                        std::cout<< "above";
                        map.AddConnection(weighted_connection,node_num, node_num - num_spaces_per_side_);
                    }
                }
                if (row < num_spaces_per_side_ - 1) {
                    if (image_[row + 1][col] == SpaceState::Normal) {
                        map.AddConnection(normal_connection,node_num, node_num + num_spaces_per_side_);
                    } else if (image_[row + 1][col] == SpaceState::Weighted) {
                        map.AddConnection(weighted_connection,node_num, node_num + num_spaces_per_side_);
                    }
                }
                if (col > 0) {
                    if (image_[row][col - 1] == SpaceState::Normal) {
                        map.AddConnection( normal_connection, node_num, node_num - 1);
                    } else if (image_[row][col - 1] == SpaceState::Weighted) {
                        map.AddConnection(weighted_connection, node_num, node_num - 1);
                    }
                }
                if (col < num_spaces_per_side_ - 1) {
                    if (image_[row][col + 1] == SpaceState::Normal) {
                        map.AddConnection(normal_connection, node_num, node_num + 1);
                    } else if (image_[row][col + 1] == SpaceState::Weighted) {
                        map.AddConnection(weighted_connection,node_num, node_num + 1);
                    }
                }
            }
            node_num++;
        }
    }
    return map;
}
}
