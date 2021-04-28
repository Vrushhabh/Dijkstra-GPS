//#include <graphics/path_finder_map.h>
#include <vector>
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../../../../include/glm/vec2.hpp"

namespace pathfinder {
class Space {
  public:
    /**
     * The Space is a space on the board
     * In computer science terms this is basically a node
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
     * Adds an connection(or edge) to this space
     * @param the id of the space that is being connected to the object
     * @param weight the weight of the connection between the 2 nodes
     */
    void AddConnection(size_t id, size_t weight);

    size_t GetId();

  private:
    /**
     * The id that distinguishes the space from other spaces on the gps
     */
    size_t id_;

    /**
     * The list of connections and the correlating weights of the connections
     * the first element in the vec2 is the weight of the connection and
     * the second is the id of the other space that is connected
     */
    std::vector<glm::vec2>  connections_ = std::vector<glm::vec2>();
};

}
