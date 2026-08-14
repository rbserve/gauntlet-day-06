#pragma once
#include <vector>
#include <string>


// Grid.hpp
struct Cell { 
    int x, y;
    bool operator==(const Cell& other) const {
        return this->x == other.x && this->y == other.y;
    }
};

class Grid {
public:
    static Grid load(const std::string& path);
    bool inBounds(Cell c) const;
    bool isOpen(Cell c) const;                   // in bounds and not '#'
    std::vector<Cell> neighbours(Cell c) const;  // walkable 4-neighbours
    Cell start() const;   // the 'S'
    Cell goal()  const;   // the 'G'
    char at(Cell c) const;
    std::string displayMap() const;
    std::string displayCell(Cell c) const;
private:
    std::vector<std::string> m_grid;
    int m_length;
    int m_height;
};