#include <vector>
#include <cmath>
#include <algorithm> 
#include <queue>
#include <cstdlib>
#include <ctime>

#include <assert.h>
#include<iostream>

// Create LinkedList and queue

// While items in cone_positions
// If items in queue
//      Pop item off of queue 
//      Iterate through all other cone positions adding entries within DISTANCE_BETWEEN_CONES
//          in order around the current cone (one that was popped). Remove cones from cone 
//          positions while iterating and add to the queue.
// else
//      Need to get a random cone (just take the last one in cone_positions)
//      Remove this from cone_positions and add to walls vector of linked list
//      Save reference to that linked list node into the queue

#define DISTANCE_BETWEEN_CONES 5

inline int distance(int &first, int &second) {
    return std::abs(second - first);
}

class Node {
    public:
        int value;
        Node *next;
        Node *prev;
};

class LinkedList {
    public:
        Node *head;
        int size;
};

std::vector<std::vector<int>> updateMap(std::vector<int> &cone_positions) {
    std::vector<LinkedList> localWalls;
    std::queue<Node *> cone_queue;
    while (!cone_positions.empty()) {
        if (!cone_queue.empty()) {
            Node *curr = cone_queue.front();
            cone_queue.pop();

            for (auto cone = cone_positions.begin(); cone < cone_positions.end(); cone++) {
                if (distance(*cone, curr->value) <= DISTANCE_BETWEEN_CONES) {
                    Node *cone_to_add = nullptr;

                    // Add new Node. Must maintain the head ptr when added before
                    if (curr->value > *cone) {
                        cone_to_add = new Node{*cone, curr, curr->prev};
                        curr->prev = cone_to_add;
                        localWalls.back().head = cone_to_add;
                    } else {
                        cone_to_add = new Node{*cone, curr->next, curr};
                        curr->next = cone_to_add;
                    }
                    localWalls.back().size++;
                    cone_queue.push(cone_to_add);
                    cone_positions.erase(cone--);
                }
            }
        } else {
            Node *new_cone = new Node{cone_positions.back(), nullptr, nullptr};
            cone_queue.push(new_cone);
            localWalls.push_back(LinkedList{new_cone, 1});
            cone_positions.pop_back();
        }
    }

    std::vector<std::vector<int>> walls;
    for (LinkedList wall: localWalls) {
        int wall_array_to_return[wall.size];

        Node *curr = wall.head;
        for (int i = 0; i < wall.size; i++) {
            wall_array_to_return[i] = curr->value;
            curr = curr->next;
            if (curr && curr->prev) {
                delete curr->prev;
            }
        }

        std::vector<int> wall_to_return;
        wall_to_return.insert(wall_to_return.cend(), &(wall_array_to_return[0]), &(wall_array_to_return[wall.size]));
        walls.push_back(wall_to_return);
    }
    return walls;
}

void print(std::vector <int> const &a) {
    std::cout << "The vector elements are : ";

    for(int i=0; i < a.size(); i++)
        std::cout << a.at(i) << ' ';

    std::cout << "\n";
}

int main(int argc, char const *argv[]) {
    std::vector<int> cone_positions = {5,10,15,20,25,30,35,40,105,110,115,120,125,130,135,140};
    // std::vector<int> cone_positions = {140,120,115,110,5,15,30,125,135,10,35,40,20,105,25,130};
    std::srand(std::time(0));
    std::random_shuffle(cone_positions.begin(), cone_positions.end());
    std::vector<int> saved_positions = cone_positions;
    std::vector<std::vector<int>> walls = updateMap(cone_positions);

    assert(walls.size() == 2);
    std::vector<int> first_half = {5,10,15,20,25,30,35,40};
    std::vector<int> second_half = {105,110,115,120,125,130,135,140};
    
    print(walls[0]);
    print(walls[1]);
    print(first_half);
    print(second_half);
    print(saved_positions);

    return 0;
}
