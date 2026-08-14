#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <cmath>
#include "Grid.hpp"

//campare operator for maps
bool operator<(const Cell& a, const Cell& b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

struct Node { Cell cell; int f; };// f = g + h
struct ByF { bool operator()(const Node& a, const Node& b){ return a.f > b.f; } };

//reconstruct final path
//cell -> parent map
std::vector<Cell> reconstruct(std::map<Cell, Cell>& cameFrom, Cell currentPath){
    std::vector<Cell> finalPath;
    finalPath.push_back(currentPath);

    while (cameFrom.find(currentPath) != cameFrom.end()){
        currentPath = cameFrom[currentPath];
        finalPath.push_back(currentPath);
        
    }
    
    return finalPath;
};

//calculate h cost
int h(const Cell& start, const Cell& goal){
    return std::hypot((goal.x - start.x), (goal.y - start.y));
}

int aStar(const Grid& grid, const Cell& start, const Cell& goal){
    std::priority_queue<Node, std::vector<Node>, ByF> open;   // min-heap on f
    std::map<Cell, Cell> cameFrom; // map cell -> parent map, for construct shortest path
    std::map<Cell, int> g; //g cost map 

    // sketch. g[]: best cost so far per cell; open: min-heap keyed on f = g + h
    // every cell's g starts at "infinity" (e.g. INT_MAX, or an absent map entry)
    g[start] = 0;                                    // paid nothing yet; forget this and the search is dead
    open.push({start, h(start, goal)});
    while (!open.empty()) {
        Node cur = open.top(); open.pop();            // cheapest-looking cell in the frontier
        if (cur.cell == goal) return reconstruct(cameFrom, goal).size();   // popped = its cost is settled
        for (Cell nb : grid.neighbours(cur.cell)) {
            int tentativeG = g[cur.cell] + 1;          // cost to reach nb via cur (uniform step cost 1)
            
            auto it = g.find(nb);
            if (it == g.end() || tentativeG < it->second) {                   // strictly cheaper than any known route to nb
                g[nb] = tentativeG;                     // record the better route
                cameFrom[nb] = cur.cell;                // and who found it, for reconstruction
                open.push({nb, tentativeG + h(nb, goal)});   // f = paid so far + optimistic remainder
            }
        }
    }
    return -1;   // frontier drained without reaching the goal: no path exists

    
};


int main(int argc, char* argv[]){

    if (argc != 2){
        std::cout << "incorrect number of argument";
        return 0;
    }

    //load the maps from argument
    Grid grid = Grid::load(argv[1]);

    // ... A* loop (see Concepts) fills cameFrom ...
    int path = aStar(grid, grid.start(), grid.goal());
    if (path != -1){
        std::cout << grid.displayMap();
        std::cout << "path length: " << path - 1 << '\n';  // edges, not cells
    }else{
        std::cout << "no path\n";
    }
    

    return 0;
};