#include "HumanPlayerStrategy.hpp"
#include "Utility/Board.hpp"
#include "Utility/Position.hpp"
#include <iostream>
#include <limits>

namespace PlayerStrategies {
namespace ConcreteStrategies {

HumanPlayerStrategy::HumanPlayerStrategy(const std::string& playerName) 
    : playerName(playerName) {}

Utility::Position HumanPlayerStrategy::makeMove(const std::shared_ptr<Utility::Board>& board) {
    while (true) {
        std::cout << playerName << ", enter your move (row [0-2] and column [0-2]): ";
        
        int row, col;
        if (std::cin >> row >> col) {
            Utility::Position move(row, col);
            if (board->isValidMove(move)) {
                return move;
            }
            std::cout << "Invalid move. Try again." << std::endl;
        } else {
            std::cout << "Invalid input. Please enter row and column as numbers." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

} // namespace ConcreteStrategies
} // namespace PlayerStrategies 