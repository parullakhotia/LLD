#include "Color.hpp"

namespace ColorUtils {
    const char* toString(Color color) {
        switch (color) {
            case Color::WHITE: return "White";
            case Color::BLACK: return "Black";
            default: return "Unknown";
        }
    }
    
    Color opposite(Color color) {
        return (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }
} 