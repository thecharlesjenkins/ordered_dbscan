#include <vector>
#include <cmath>
#include <algorithm> 

#define DISTANCE_BETWEEN_CONES 100

int distance(int first, int second) {
    return std::abs(second - first);
}

void updateMap(std::vector<int> &cone_positions, std::vector<std::vector<int>> &walls) {
    while (!cone_positions.empty()) {
        std::vector<int> localCones;
        int curr = cone_positions.back();
        cone_positions.pop_back();

        localCones.push_back(curr);

        for (auto cone = cone_positions.begin(); cone < cone_positions.end(); cone++) {
            if (distance(*cone, curr) < DISTANCE_BETWEEN_CONES) {
                localCones.push_back(*cone);
                cone = cone_positions.erase(cone);
            }
        }

        walls.emplace_back(localCones);
    }
}

int main(int argc, char const *argv[]) {
    std::vector<std::vector<int>> walls;
    std::vector<int> cone_positions = {5,10,15,20,25,30,35,40,105,110,115,120,125,130,135,140};
    std::random_shuffle(cone_positions.begin(), cone_positions.end());
    updateMap(cone_positions, walls);

    return 0;
}
