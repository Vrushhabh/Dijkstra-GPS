#include "gps/map.h"
#include <queue>
#include <map>

namespace pathfinder {
Map::Map(){}

void Map::AddSpace(Space space) {
    spaces_.emplace_back(space);
}

Space& Map::GetSpace(size_t id) {
    for (size_t i = 0; i < spaces_.size(); i++) {
        if (id == spaces_[i].GetId()){
                return spaces_[i];
        }
    }
    throw std::invalid_argument("Space does not exist in map currently");
}

void Map::AddConnection(size_t weight, size_t space_one, size_t space_two) {
    for (Space &space : spaces_) {
        if (space.GetId() == space_one) {
               space.AddConnection(space_two, weight);
           }
        if (space.GetId() == space_two) {
                space.AddConnection(space_one, weight);
           }
    }
}


int Map::FindShortestPath(size_t start_space_id, size_t end_space_id) {
    //A reference I used to make sure I implemented the algorithm right was from this
    //geeksforgeeks article
    // https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
    //Space ID is the key and the value is the distance from start space
    std::map<size_t, size_t> dist_from_start_space;
    std::map<size_t, size_t> previous_map;
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>,
    std::greater<std::pair<size_t, size_t>>> pq;
    // set all distances to the max value because we do not know how far the
    //the value is from the start node
    for (size_t i = 0; i < spaces_.size(); i++) {
        //We need to use INT_MAX because we need a very high value for not knowing
        //the distance of the nodes from the starting node
        //INFINITY could not be used because the value defaults to zero
        //for some odd technical issue probably relating to types
        dist_from_start_space.insert({spaces_[i].GetId(), INT_MAX});
    }
    // The starting node's distance is zero because we already know
    // where the starting node is and its distance from itself
    dist_from_start_space[start_space_id] = 0;
    pq.push(std::make_pair(0, start_space_id));
    while (!pq.empty()) {
        //first get the space from the priority queue before popping it out of pq
        Space curr_space = GetSpace(pq.top().second);
        pq.pop();
        for (size_t edge_num = 0; edge_num < curr_space.GetConnections().size(); edge_num++) {
            //Updates the distance for current from the distance from starting destination
            int new_dist = dist_from_start_space[curr_space.GetId()]
                    + curr_space.GetConnections()[edge_num].y;
            // check if new distance is smaller than previous distance
            if (dist_from_start_space[curr_space.GetConnections()[edge_num].x] > new_dist) {
                dist_from_start_space[curr_space.GetConnections()[edge_num].x] = new_dist;
                //for each connection it adds to the priority queue and is queued depending
                pq.push(std::make_pair(new_dist, curr_space.GetConnections()[edge_num].x));
                previous_map.insert({static_cast<size_t>(curr_space.GetConnections()[edge_num].x)
                                     ,static_cast<size_t>(curr_space.GetId())});
            }
        }
    }

        // update shortest path
        std::vector<int> shortest_path;
        int current_id = end_space_id;
        while (current_id != start_space_id) {
            shortest_path.push_back(current_id);
            current_id = previous_map[current_id];
        }
        shortest_path.push_back(start_space_id);
        // If the destination was not reached we would return -1 to let the program know it is impossible
        if (dist_from_start_space[end_space_id] == INT_MAX) {
            return -1;
        }
        shortest_path_ = shortest_path;
        // return the distance to the node
         return dist_from_start_space[end_space_id];
}
std::vector<int> Map::GetShortestPath() {
    return shortest_path_;
};
}
