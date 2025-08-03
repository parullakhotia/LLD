#include "Symbol.hpp"
#include <string>

namespace CommonEnum {

std::string symbolToString(Symbol symbol) {
    switch (symbol) {
        case Symbol::X:
            return "X";
        case Symbol::O:
            return "O";
        case Symbol::EMPTY:
            return "EMPTY";
        default:
            return "UNKNOWN";
    }
}

char symbolToChar(Symbol symbol) {
    switch (symbol) {
        case Symbol::X:
            return 'X';
        case Symbol::O:
            return 'O';
        case Symbol::EMPTY:
            return '.';
        default:
            return '?';
    }
}

} // namespace CommonEnum 