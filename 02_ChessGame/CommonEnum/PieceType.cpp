#include "PieceType.hpp"

namespace PieceTypeUtils {
    const char* toString(PieceType type) {
        switch (type) {
            case PieceType::PAWN: return "Pawn";
            case PieceType::ROOK: return "Rook";
            case PieceType::KNIGHT: return "Knight";
            case PieceType::BISHOP: return "Bishop";
            case PieceType::QUEEN: return "Queen";
            case PieceType::KING: return "King";
            default: return "Unknown";
        }
    }
    
    char getSymbol(PieceType type) {
        switch (type) {
            case PieceType::PAWN: return 'P';
            case PieceType::ROOK: return 'R';
            case PieceType::KNIGHT: return 'N';
            case PieceType::BISHOP: return 'B';
            case PieceType::QUEEN: return 'Q';
            case PieceType::KING: return 'K';
            default: return '?';
        }
    }
    
    int getValue(PieceType type) {
        switch (type) {
            case PieceType::PAWN: return 1;
            case PieceType::ROOK: return 5;
            case PieceType::KNIGHT: return 3;
            case PieceType::BISHOP: return 3;
            case PieceType::QUEEN: return 9;
            case PieceType::KING: return 0; // Infinite value
            default: return 0;
        }
    }
} 