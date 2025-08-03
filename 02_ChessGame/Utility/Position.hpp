#pragma once
#include <string>

class Position {
private:
    int row;
    int col;

public:
    Position(int row, int col);
    
    // Getters
    int getRow() const;
    int getCol() const;
    
    // Utility methods
    bool isValid() const;
    std::string toAlgebraic() const;
    static Position fromAlgebraic(const std::string& notation);
    
    // Operators
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    
    // Static constants
    static const int BOARD_SIZE = 8;
}; 