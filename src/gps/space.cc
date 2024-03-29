#include <gps/space.h>

namespace pathfinder {
Space::Space(size_t marker) {
    id_ = marker;
}

std::vector<glm::vec2> Space::GetConnections() const {
    return connections_;
}

void Space::AddConnection(size_t id, size_t weight) {
    glm::vec2 connection = glm::vec2(id, weight);
    connections_.emplace_back(connection);
}

size_t Space::GetId() {
    return id_;
}
}
