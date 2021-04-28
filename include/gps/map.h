#include "space.h"
#include <queue>
namespace pathfinder {
class Map {
public:
  /**
   * The default constructor that makes a Map no spaces in
   * it or in lame terms a graph with no nodes
   */
  Map();
  /**
   * Adds a space to the map
   * @param space The space that is being added
   */
  void AddSpace(Space& space);

  /**
   * Adds a connection between two nodes
   * @param weight The weight of a connection (The more the weight the more
   * "time" it takes to reach the destination or the less desired the connection is)
   * Pointers could also be used that point to other spaces
   * @param space_one A space id that is making a connection to space_two
   * @param space_two A space id that is making a connection to space_one
   */
  void AddConnection(size_t weight, size_t space_one, size_t space_two);

   /**
     * Finds the shortest path using dijkstra's algorithm  which allows the usage of weights of connections
     * A lot of the basic background knowledge was gotten from this Computerphile video
     * https://www.youtube.com/watch?v=GazC3A4OQTE
     * @param start_space_id  The start space where the id
     * @param end_space_id The end space where the id
     * @return int The shortest distance between the start and end space
     *
     */
  int FindShortestPath(size_t start_space_id, size_t end_space_id);
  /**
   * Returns shortest path of the last FindShortestPath function call
   * This is will be used for the graphics portion of the application
   * @return
   */
  std::vector<int> GetShortestPath();

private:
   /**
    * The list of spaces in the map
    */
  std::vector<Space> spaces_;

  /**
   * vector of ids that leads to the ending node that is changed everytime
   * FindShortestPath function is called
   * Originally set to just contain  a -1 to let the program know it has not been called
   */
  std::vector<int> shortest_path_ = std::vector<int> (1, -1);

  /**
   * Gets the space from the map from using the space id
   * @param id The  value that can identify the space
   * @return space
   */
  Space& GetSpace(size_t id);
};

}



