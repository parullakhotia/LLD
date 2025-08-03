#pragma once

enum class PieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

// Utility functions for PieceType
namespace PieceTypeUtils {
    const char* toString(PieceType type);
    char getSymbol(PieceType type);
    int getValue(PieceType type);
} 