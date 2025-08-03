#pragma once

#include "GameStateHandler/GameState.hpp"

namespace GameStateHandler {
namespace ConcreteStates {

class InProgressState : public GameState {
public:
    void handle(std::shared_ptr<Utility::Player> player) override;
    bool isGameOver() const override { return false; }
};

} // namespace ConcreteStates
} // namespace GameStateHandler 