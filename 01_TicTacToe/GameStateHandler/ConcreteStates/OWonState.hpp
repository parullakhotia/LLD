#pragma once

#include "GameStateHandler/GameState.hpp"

namespace GameStateHandler {
namespace ConcreteStates {

class OWonState : public GameState {
public:
    void handle(std::shared_ptr<Utility::Player> player) override;
    bool isGameOver() const override { return true; }
};

} // namespace ConcreteStates
} // namespace GameStateHandler 