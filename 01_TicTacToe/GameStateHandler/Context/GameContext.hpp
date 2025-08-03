#pragma once

#include <memory>
#include "GameStateHandler/GameState.hpp"

// Forward declaration
namespace Utility {
    class Player;
}

namespace GameStateHandler {
namespace Context {

class GameContext {
private:
    std::shared_ptr<GameState> currentState;
    bool gameOver;

public:
    GameContext();
    
    void next(std::shared_ptr<Utility::Player> player, bool isWin);
    std::shared_ptr<GameState> getCurrentState() const { return currentState; }
    bool isGameOver() const { return gameOver; }
    
    void setState(std::shared_ptr<GameState> state);
};

} // namespace Context
} // namespace GameStateHandler 