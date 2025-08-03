#include "Controller/GameController/TicTacToeGame.hpp"
#include "PlayerStrategies/ConcreteStrategies/HumanPlayerStrategy.hpp"
#include <memory>

int main() {
    // Create player strategies
    auto playerXStrategy = std::make_shared<PlayerStrategies::ConcreteStrategies::HumanPlayerStrategy>("Player X");
    auto playerOStrategy = std::make_shared<PlayerStrategies::ConcreteStrategies::HumanPlayerStrategy>("Player O");
    
    // Create and start the game
    Controller::GameController::TicTacToeGame game(playerXStrategy, playerOStrategy, 3, 3);
    game.play();
    
    return 0;
} 