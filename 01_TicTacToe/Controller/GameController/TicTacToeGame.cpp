#include "TicTacToeGame.hpp"
#include "Utility/Board.hpp"
#include "Utility/Player.hpp"
#include "CommonEnum/Symbol.hpp"
#include "GameStateHandler/Context/GameContext.hpp"
#include "GameStateHandler/ConcreteStates/XWonState.hpp"
#include "GameStateHandler/ConcreteStates/OWonState.hpp"
#include "GameStateHandler/ConcreteStates/DrawState.hpp"
#include <iostream>

namespace Controller {
namespace GameController {

TicTacToeGame::TicTacToeGame(std::shared_ptr<PlayerStrategies::PlayerStrategy> xStrategy,
                               std::shared_ptr<PlayerStrategies::PlayerStrategy> oStrategy,
                               int rows, int columns) {
    board = std::make_shared<Utility::Board>(rows, columns);
    playerX = std::make_shared<Utility::Player>(CommonEnum::Symbol::X, xStrategy);
    playerO = std::make_shared<Utility::Player>(CommonEnum::Symbol::O, oStrategy);
    currentPlayer = playerX;
    gameContext = std::make_shared<GameStateHandler::Context::GameContext>();
}

void TicTacToeGame::play() {
    do {
        // Print the current state of the game
        board->printBoard();
        
        // Current player makes the move
        Utility::Position move = currentPlayer->getPlayerStrategy()->makeMove(board);
        board->makeMove(move, currentPlayer->getSymbol());
        
        // Check game state for win/draw
        board->checkGameState(gameContext, currentPlayer);
        
        switchPlayer();
    } while (!gameContext->isGameOver());
    
    announceResult();
}

void TicTacToeGame::switchPlayer() {
    currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
}

void TicTacToeGame::announceResult() {
    auto state = gameContext->getCurrentState();
    board->printBoard();
    state->handle(currentPlayer);
}

} // namespace GameController
} // namespace Controller 