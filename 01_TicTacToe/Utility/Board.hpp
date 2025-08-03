#pragma once

#include <vector>
#include <memory>
#include "CommonEnum/Symbol.hpp"
#include "Position.hpp"

// Forward declarations
namespace GameStateHandler {
    namespace Context {
        class GameContext;
    }
}

namespace Utility {

class Player;

class Board {
private:
    int rows;
    int columns;
    std::vector<std::vector<CommonEnum::Symbol>> grid;

public:
    Board(int rows, int columns);
    
    // Board operations
    bool isValidMove(const Position& pos) const;
    void makeMove(const Position& pos, CommonEnum::Symbol symbol);
    void checkGameState(std::shared_ptr<GameStateHandler::Context::GameContext> context, 
                       std::shared_ptr<Player> currentPlayer);
    
    // Display
    void printBoard() const;
    
    // Getters
    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    CommonEnum::Symbol getSymbol(int row, int col) const { return grid[row][col]; }
    
    // Check if board is full
    bool isFull() const;

private:
    bool isWinningLine(const std::vector<CommonEnum::Symbol>& line) const;
    std::vector<CommonEnum::Symbol> getRow(int row) const;
    std::vector<CommonEnum::Symbol> getColumn(int col) const;
    std::vector<CommonEnum::Symbol> getDiagonal1() const;
    std::vector<CommonEnum::Symbol> getDiagonal2() const;
};

} // namespace Utility 