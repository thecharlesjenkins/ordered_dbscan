#include <vector>
#include <cmath>
#include <algorithm> 
#include <queue>

#define DISTANCE_BETWEEN_CONES 5

int distance(int first, int second) {
    return std::abs(second - first);
}

// HOW TO:

// Create Linked-List style thing

// WALL
// Need to get a random cone (just take the last one in cone_positions)
// Remove this from cone_positions and add to walls vector of linked list
// Save reference to that linked list node into a queue

// LABEL
// Pop item off of queue 
// Iterate through all other cone positions adding entries within DISTANCE_BETWEEN_CONES
//      in order around the current cone (one that was popped). Remove cones from cone 
//      positions while iterating and add to the queue.
// If items left in queue, branch to LABEL

// If items left in cone_positions branch to WALL

void updateMap(std::vector<int> &cone_positions, std::vector<std::vector<int>> &walls) {
    int curr = cone_positions.back();
    cone_positions.pop_back();


    walls.push_back({curr});
    std::queue<int> queue;
    queue.push(curr);

    walls[0].insert(curr, 1);

    while (!cone_positions.empty()) {
        bool added = false;
        for(auto wall = walls.begin(); wall < walls.end() && !added; wall++) {
            for (auto cone = (*wall).begin(); cone < (*wall).end() && !added; cone++) {
                if (distance(*cone, curr) <= DISTANCE_BETWEEN_CONES) {
                    if (curr > *cone) {
                        wall->insert(cone, curr);
                    } else {
                        wall->insert(cone + 1, curr);
                    }
                    curr = *cone;
                    cone = cone_positions.erase(cone);
                    added = true;
                } 
            }
        }
        if (!added) {
            walls.push_back({curr});
            curr = cone_positions.back();
            cone_positions.pop_back();
        }
    }
}

int main(int argc, char const *argv[]) {
    std::vector<std::vector<int>> walls;
    std::vector<int> cone_positions = {5,10,15,20,25,30,35,40,105,110,115,120,125,130,135,140};
    std::random_shuffle(cone_positions.begin(), cone_positions.end());
    updateMap(cone_positions, walls);

    return 0;
}
