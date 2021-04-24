//
// Created by Vrushhabh Patel on 4/23/21.
//
#include "space.h"

namespace pathfinder {
class Map {
public:
  Map();
  /**
   * Adds a space to the map
   * @param space The space that is being added
   */
  void AddSpace(Space& space);

  /**
   * Gets the space from the map from using the space id
   * @param id The  value that can identify the space
   * @return space
   */
  Space GetSpace(size_t id);

  /**
   * Adds a connection between two nodes
   * @param weight The weight of a connection (The more the weight the more
   * "time" it takes to reach the destination)
   * @param space_one A space id that is making a connection to space_two
   * @param space_two A space id that is making a connection to space_one
   */
  void AddConnection(size_t weight, size_t space_one, size_t space_two);



private:
    /**
     * The list of spaces in the map
     */
    std::vector<Space> spaces_;
};

}



