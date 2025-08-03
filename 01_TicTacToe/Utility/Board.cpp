#include "Board.hpp"
#include "Player.hpp"
#include "GameStateHandler/Context/GameContext.hpp"
#include "CommonEnum/Symbol.hpp"
#include <iostream>
#include <algorithm>

namespace Utility {

Board::Board(int rows, int columns) : rows(rows), columns(columns) {
    grid.resize(rows, std::vector<CommonEnum::Symbol>(columns, CommonEnum::Symbol::EMPTY));
}

bool Board::isValidMove(const Position& pos) const {
    return pos.row >= 0 && pos.row < rows && 
           pos.col >= 0 && pos.col < columns && 
           grid[pos.row][pos.col] == CommonEnum::Symbol::EMPTY;
}

void Board::makeMove(const Position& pos, CommonEnum::Symbol symbol) {
    grid[pos.row][pos.col] = symbol;
}

void Board::checkGameState(std::shared_ptr<GameStateHandler::Context::GameContext> context, 
                          std::shared_ptr<Player> currentPlayer) {
    // Check rows
    for (int i = 0; i < rows; i++) {
        auto row = getRow(i);
        if (row[0] != CommonEnum::Symbol::EMPTY && isWinningLine(row)) {
            context->next(currentPlayer, true);
            return;
        }
    }
    
    // Check columns
    for (int i = 0; i < columns; i++) {
        auto column = getColumn(i);
        if (column[0] != CommonEnum::Symbol::EMPTY && isWinningLine(column)) {
            context->next(currentPlayer, true);
            return;
        }
    }
    
    // Check diagonals
    auto diagonal1 = getDiagonal1();
    if (diagonal1[0] != CommonEnum::Symbol::EMPTY && isWinningLine(diagonal1)) {
        context->next(currentPlayer, true);
        return;
    }
    
    auto diagonal2 = getDiagonal2();
    if (diagonal2[0] != CommonEnum::Symbol::EMPTY && isWinningLine(diagonal2)) {
        context->next(currentPlayer, true);
        return;
    }
    
    // Check for draw
    if (isFull()) {
        context->next(currentPlayer, false);
    }
}

bool Board::isWinningLine(const std::vector<CommonEnum::Symbol>& line) const {
    if (line.empty()) return false;
    CommonEnum::Symbol first = line[0];
    return std::all_of(line.begin(), line.end(), [first](CommonEnum::Symbol s) {
        return s == first;
    });
}

std::vector<CommonEnum::Symbol> Board::getRow(int row) const {
    return grid[row];
}

std::vector<CommonEnum::Symbol> Board::getColumn(int col) const {
    std::vector<CommonEnum::Symbol> column;
    for (int i = 0; i < rows; i++) {
        column.push_back(grid[i][col]);
    }
    return column;
}

std::vector<CommonEnum::Symbol> Board::getDiagonal1() const {
    std::vector<CommonEnum::Symbol> diagonal;
    int size = std::min(rows, columns);
    for (int i = 0; i < size; i++) {
        diagonal.push_back(grid[i][i]);
    }
    return diagonal;
}

std::vector<CommonEnum::Symbol> Board::getDiagonal2() const {
    std::vector<CommonEnum::Symbol> diagonal;
    int size = std::min(rows, columns);
    for (int i = 0; i < size; i++) {
        diagonal.push_back(grid[i][columns - 1 - i]);
    }
    return diagonal;
}

bool Board::isFull() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == CommonEnum::Symbol::EMPTY) {
                return false;
            }
        }
    }
    return true;
}

void Board::printBoard() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            CommonEnum::Symbol symbol = grid[i][j];
            switch (symbol) {
                case CommonEnum::Symbol::X:
                    std::cout << " X ";
                    break;
                case CommonEnum::Symbol::O:
                    std::cout << " O ";
                    break;
                case CommonEnum::Symbol::EMPTY:
                default:
                    std::cout << " . ";
            }
            
            if (j < columns - 1) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        
        if (i < rows - 1) {
            std::cout << "---+---+---" << std::endl;
        }
    }
    std::cout << std::endl;
}

} // namespace Utility 