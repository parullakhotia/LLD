#pragma once

namespace Utility {

class Position {
public:
    int row;
    int col;
    
    Position(int row, int col);
    Position(const Position& other);
    Position& operator=(const Position& other);
    
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
};

} // namespace Utility 