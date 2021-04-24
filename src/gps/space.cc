//
// Created by Vrushhabh Patel on 4/23/21.
//

#include <gps/space.h>

namespace pathfinder {
  Space::Space(size_t marker) {
    id_ = marker;

  }

  std::vector<glm::vec2> Space::GetConnections() const {
    return connections_;
  }

  void Space::AddConnection(size_t id, size_t weight) {

  }

  size_t Space::GetId(size_t id) {
      return id_;
  }
}
