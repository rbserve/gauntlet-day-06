#include <iostream>
#include <vector>
#include "Grid.hpp"

//run the file like the format below
// ./grid <map> <x> <y> [<x> <y> ...].
int main(int argc, char* argv[]){
    std::vector<Cell> cells;
    for (int i = 2; i<argc-1;){
        cells.push_back(Cell{std::stoi(argv[i]), std::stoi(argv[i+1])});
        i += 2;
    }

    //load the maps from argument
    Grid grid = Grid::load(argv[1]);

    //print out map
    std::cout << grid.displayMap();

    //print Start
    std::cout << "start S = " << grid.displayCell(grid.start()) << std::endl;

    // //print Goal
    std::cout << "goal G = " << grid.displayCell(grid.goal()) << std::endl;

    //print neightbours cells
    for (Cell c : cells){
        std::cout << "neightbours" + grid.displayCell(c) +":";
        for (Cell neighbour : grid.neighbours(c)){
            std::cout << grid.displayCell(neighbour) + " ";
        }
        std::cout << std::endl;
    }

    return 0;
};