//
// Created by Vrushhabh Patel on 4/20/21.
//

#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>
#include <gps/map.h>

namespace pathfinder {
namespace  graphics {
enum class SpaceState {
    Blocked,
    Normal,
    Weighted,
};

class PathFinderMap {
  public:
    /**
     * The naive-bayes grid lay out made sense for a gps so the project is heavily inspired and shares
     * a good bit of code from that in the visual aspect
     * so are the draw in functions because user interacts similarly to the sketchpad class
     * @param top_left_corner The top left of the grid
     * @param num_spaces_per_side How many spaces are in each side of the gps
     * @param map_size The actual size of the gps on the screen
     * @param brush_radius The size of the brush that is used to draw certain types of spaces
     */
    PathFinderMap(const glm::vec2 &top_left_corner,
                        size_t num_spaces_per_side, double map_size,
                        double brush_radius);

    /**
     * Draws the actual gps on the browser with the space types of different colors
     */
    void DrawMap();

    /**
     * Adds weight to the selected nodes and changes there color to purple
     * @param brush_screen_coords The coordinate of the mouse
     */
    void WeightAdder(const glm::vec2 &brush_screen_coords);

    /**
     * @param brush_screen_coords The coordinate of the mouse
     */
    void BlockAdder(const cinder::vec2& brush_screen_coords);

    /**
     * Makes a map with correct connections and
     */
     Map MakeMap();


    /**
     * Finds the shortest path on the map and highlights the path in light green
     */
    void FindShortestPath();

    /**
     *Clears the board and sets every space to be a normal white space
     */
    void Clear();
  private:
    glm::vec2 top_left_corner_;

    /**
     * Length of the gps which is dictated by spaces
     */
    size_t num_spaces_per_side_;

    /** How big one space is in */
    double space_side_length_;

    /**
     * The radius of the brush used on the gps to color in spaces to indicate their appropiate type
     */
    double brush_radius_;

    /**
     * This vector represents what in the image. There will be different types of spaces including blocks and
     * spaces that would be the equivalent of moving more than just one space.
     * The enum type makes it so th spaces are standardized in 3 visual states that the user
     * has control over
     */
    std::vector<std::vector<SpaceState>> image_;
};
}
}



