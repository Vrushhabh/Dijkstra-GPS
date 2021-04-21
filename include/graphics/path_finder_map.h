//
// Created by Vrushhabh Patel on 4/20/21.
//


#include <glm/vec2.hpp>

namespace pathfinder {
namespace  graphics {
class PathFinderMap {
  public:
    PathFinderMap(const glm::vec2 &top_left_corner,
                        size_t num_spaces_per_side, double sketchpad_size,
                        double brush_radius = .8);
    void DrawMap();
  private:
    glm::vec2 top_left_corner_;

    /**
     * Length of the map which is dictated by spaces
     */
    size_t num_spaces_per_side_;

    /** How big one space is in  */
    double space_side_length_;

    /**
     * The radius of the brush used on the map to color in spaces to indicate their appropiate type
     */
    double brush_radius_;
};
}

}



