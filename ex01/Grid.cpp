#include "Grid.hpp"
#include "fstream"
#include <vector>
#include <string>

Grid Grid::load(const std::string& path){
    Grid grid;
    std::fstream file(path);
    std::string tempLine;

    while (std::getline(file, tempLine)){
        grid.m_grid.push_back(tempLine);
    }

    grid.m_height = grid.m_grid.size();
    grid.m_length = grid.m_grid[0].size();


    file.close();
    return grid;
};

bool Grid::inBounds(Cell c) const{
    return  c.x >= 0 &&
            c.x < m_length &&
            c.y >= 0 &&
            c.y < m_height;
};

bool Grid::isOpen(Cell c) const{
    return inBounds(c) && at(c) != '#';
}; // in bounds and not '#'

std::vector<Cell> Grid::neighbours(Cell c) const{
    std::vector<Cell> out;
    const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};   // pair i = one step: (+1,0) right,
    for (int i = 0; i < 4; ++i) {                           // (-1,0) left, (0,+1) down, (0,-1) up
        Cell n{c.x + dx[i], c.y + dy[i]};
        if (isOpen(n)) out.push_back(n); // silently drop off-map cells and walls
    }
    return out;
};  // walkable 4-neighbours

Cell Grid::start() const{
    for (int i = 0; i < m_length; ++i){
        for (int j = 0; j < m_height; ++j){
            Cell c{i,j};
            if (at(c) == 'S'){
                return c;
            }
        }
    }
    return Cell{-1,-1};
};   // the 'S'

Cell Grid::goal()  const{
    for (int i = 0; i < m_length; ++i){
        for (int j = 0; j < m_height; ++j){
            Cell c{i,j};
            if (at(c) == 'G'){
                return c;
            }
        }
    }
    return Cell{-1,-1};
};   // the 'G'

//helper functions
char Grid::at(Cell c) const {
    return m_grid[c.y][c.x];
};

std::string Grid::displayMap() const{
    std::string map;

    for (std::string line : m_grid){
        map += line + "\n";
    }
    return map;
};

std::string Grid::displayCell(Cell c) const{
    return "(" + std::to_string(c.x) + ", " + std::to_string(c.y) + ")";
};