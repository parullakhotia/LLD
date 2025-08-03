#pragma once

namespace CommonEnum {

enum class Symbol {
    X,
    O,
    EMPTY
};

// Utility functions for Symbol enum
std::string symbolToString(Symbol symbol);
char symbolToChar(Symbol symbol);

} // namespace CommonEnum 