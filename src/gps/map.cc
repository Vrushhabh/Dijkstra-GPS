//
// Created by Vrushhabh Patel on 4/23/21.
//

#include "gps/map.h"
#include <iostream>

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
  };
}
