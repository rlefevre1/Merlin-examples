#include "a_star_example.hpp"

#include <iostream>

int main()
{
    // Create the map
    simple_map_t map {{1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                      {1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
                      {1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
                      {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
                      {1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
                      {1, 1, 0, 1, 1, 0, 0, 1, 1, 1},
                      {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}};

    // Create the initial state
    merl::AStar::State * init_state = new LocationState(0, 7, 9, 5, map);

    // Run the A* algorithm
    merl::AStar as(merl::AStar::MODE::MINIMIZE);
    std::list<merl::AStar::State*> solution = as.launch(init_state);

    // Draw the solution path
    for(merl::AStar::State*& s : solution)
    {
        LocationState * ls = dynamic_cast<LocationState*>(s);
        map[ls->Y()][ls->X()] = 2;
    }

    // Display the solution path
    for(const auto & row : map)
    {
        for(const auto & val : row)
        {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }

    // Free memory
    merl::AStar::release_path(solution);

    return 0;
}
