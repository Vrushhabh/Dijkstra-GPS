//
// Created by Vrushhabh Patel on 4/23/21.
//

#include "gps/map.h"
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../../../../include/glm/vec2.hpp"

namespace pathfinder {
  Map::Map(){}

  void Map::AddSpace(Space &space) {
      spaces_.emplace_back(space);
  }

  Space Map::GetSpace(size_t id) {
      for (size_t i = 0; i < spaces_.size(); i++) {
          if (id == spaces_[i].GetId()){
              return spaces_[i];
          }
      }
      throw std::invalid_argument("Space does not exist in map currently");
  }

  void Map::AddConnection(size_t weight, size_t space_one, size_t space_two) {
      if (space_two == space_one) {
          throw std::invalid_argument("Space can not have connection to itself");
      }

      for (size_t i = 0; i < spaces_.size(); i++) {
          if (space_one == spaces_[i].GetId()){
              spaces_[i].AddConnection(space_two, weight);
          }
          if (space_two == spaces_[i].GetId()){
              spaces_[i].AddConnection(space_one, weight);
          }
      }
  }

    int Map::FindShortestPath(size_t start_space_id, size_t end_space_id) {
        //A reference I used to make sure I implemented the algorithm right was from this
        //geeksforgeeks article
        // https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
        std::map<size_t, size_t> dist_from_start_space;
        std::map<size_t, size_t> previous_map;
        std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>,
                std::greater<std::pair<size_t, size_t>>> pq;
        // set all distances to the max value because we do not know how far the
        //the value is from the start node
        for (size_t i = 0; i < spaces_.size(); i++) {
            dist_from_start_space.emplace(spaces_[i].GetId(),INFINITY);

        }
        // check if the starting or ending node doesnt exist, if so, return -1
        if (dist_from_start_space.count(end_space_id) == 0 ||
            dist_from_start_space.count(start_space_id) == 0) {
            return -1;
        }

        // set the distance to the starting node to 0 and push it in priority queue
        dist_from_start_space[start_space_id] = 0;
        pq.push(std::make_pair(start_space_id, 0));

        while (!pq.empty()) {
            Space u = GetSpace(pq.top().first);
            pq.pop();
            for (glm::vec2 edge : u.GetConnections()) {
                int new_dist = dist_from_start_space[u.GetId()] + edge.y;
                // check if new distance is smaller than the old distance. If so, update
                // the distance and update the previous node
                if (dist_from_start_space[edge.x] > new_dist) {
                    dist_from_start_space[edge.x] = new_dist;
                    pq.push(std::make_pair(new_dist, edge.x));
                    previous_map.emplace(edge.x, u.GetId());
                }
            }
        }

        // update shortest path
        std::vector<size_t> shortest_path;
        int current_id = end_space_id;
        while (current_id != start_space_id) {
            shortest_path.push_back(current_id);
            current_id = previous_map[current_id];
        }

        shortest_path.push_back(start_space_id);
        shortest_path_ = shortest_path;

        // Check if ending node was not reached, if so, return -1
        if (dist_from_start_space[end_space_id] == INFINITY) {
            return -1;
        }
        // return the distance to the node
        return dist_from_start_space[end_space_id];
    };
}
