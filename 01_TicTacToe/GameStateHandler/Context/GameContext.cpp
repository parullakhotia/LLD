#include "GameContext.hpp"
#include "GameStateHandler/ConcreteStates/InProgressState.hpp"
#include "GameStateHandler/ConcreteStates/XWonState.hpp"
#include "GameStateHandler/ConcreteStates/OWonState.hpp"
#include "GameStateHandler/ConcreteStates/DrawState.hpp"
#include "Utility/Player.hpp"
#include "CommonEnum/Symbol.hpp"
#include <iostream>

namespace GameStateHandler {
namespace Context {

GameContext::GameContext() : gameOver(false) {
    currentState = std::make_shared<InProgressState>();
}

void GameContext::next(std::shared_ptr<Utility::Player> player, bool isWin) {
    if (isWin) {
        if (player->getSymbol() == CommonEnum::Symbol::X) {
            currentState = std::make_shared<XWonState>();
        } else {
            currentState = std::make_shared<OWonState>();
        }
        gameOver = true;
    } else {
        // Check if it's a draw (board is full)
        currentState = std::make_shared<DrawState>();
        gameOver = true;
    }
}

void GameContext::setState(std::shared_ptr<GameState> state) {
    currentState = state;
}

} // namespace Context
} // namespace GameStateHandler 