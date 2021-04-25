#include <graphics/path_finder_map.h>
#include <vector>
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../../../../include/glm/vec2.hpp"

namespace pathfinder {
class Space {
  public:
    /**
     * The Space is a space on the board
     * @param  size_t marker This distinguishes a space on the gps from
     * another space
     */
    Space(size_t marker);

    /**
     * Gets the list of adjacent connections and the weights of the adjacent spaces
     * weights are like spaces but count as more distance a good analogy could be
     * a GPS app detecting traffic and choosing something with longer distance
     * that will take less time to reach the destination
     * @return the list of adjacent edges and weights
     */
    std::vector<glm::vec2> GetConnections() const;
    /**
     * Adds an connection to this space
     * @param the id of the space
     * @param weight the weight between the 2 nodes
     */
    void AddConnection(size_t id, size_t weight);

    /**
     * Finds the shortest path using dijkstra's  which allows the usage of weights of connections
     * A lot of the background knowledge was gotten from this Computerphile video
     * https://www.youtube.com/watch?v=GazC3A4OQTE
     * @param start_space_id  The start space where the id
     * @param end_space_id The end space where the id
     * @return The shortest distance between the start and end space
     */
    size_t FindShortestPath(size_t start_space_id, size_t end_space_id);

    size_t GetId();

  private:
    /**
     * The id that distinguishes the space from other spaces on the gps
     */
    size_t id_;

    /**
     * The list of connections and the correlating weights of the connections
     * the first element in the vec2 is the id of the space that is connected and the second is the weight
     */
    std::vector<glm::vec2>  connections_ = std::vector<glm::vec2>();
};

}
