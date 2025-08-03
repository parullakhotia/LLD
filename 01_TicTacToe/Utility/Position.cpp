#include "Position.hpp"

namespace Utility {

Position::Position(int row, int col) : row(row), col(col) {}

Position::Position(const Position& other) : row(other.row), col(other.col) {}

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        row = other.row;
        col = other.col;
    }
    return *this;
}

bool Position::operator==(const Position& other) const {
    return row == other.row && col == other.col;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}

} // namespace Utility 