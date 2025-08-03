#pragma once

enum class Color {
    WHITE,
    BLACK
};

// Utility functions for Color
namespace ColorUtils {
    const char* toString(Color color);
    Color opposite(Color color);
} 