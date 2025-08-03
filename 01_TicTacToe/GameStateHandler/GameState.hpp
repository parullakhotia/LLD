#pragma once

#include <memory>

// Forward declaration
namespace Utility {
    class Player;
}

namespace GameStateHandler {

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handle(std::shared_ptr<Utility::Player> player) = 0;
    virtual bool isGameOver() const = 0;
};

} // namespace GameStateHandler 