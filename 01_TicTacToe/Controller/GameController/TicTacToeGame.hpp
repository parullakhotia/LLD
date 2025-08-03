#pragma once

#include <memory>
#include "Controller/BoardGames.hpp"
#include "Utility/Board.hpp"
#include "Utility/Player.hpp"
#include "PlayerStrategies/PlayerStrategy.hpp"
#include "GameStateHandler/Context/GameContext.hpp"

namespace Controller {
namespace GameController {

class TicTacToeGame : public BoardGames {
private:
    std::shared_ptr<Utility::Board> board;
    std::shared_ptr<Utility::Player> playerX;
    std::shared_ptr<Utility::Player> playerO;
    std::shared_ptr<Utility::Player> currentPlayer;
    std::shared_ptr<GameStateHandler::Context::GameContext> gameContext;

public:
    TicTacToeGame(std::shared_ptr<PlayerStrategies::PlayerStrategy> xStrategy,
                   std::shared_ptr<PlayerStrategies::PlayerStrategy> oStrategy,
                   int rows, int columns);
    
    void play() override;

private:
    void switchPlayer();
    void announceResult();
};

} // namespace GameController
} // namespace Controller 