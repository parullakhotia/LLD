#pragma once

#include <memory>
#include "CommonEnum/Symbol.hpp"

// Forward declaration
namespace PlayerStrategies {
    class PlayerStrategy;
}

namespace Utility {

class Player {
private:
    CommonEnum::Symbol symbol;
    std::shared_ptr<PlayerStrategies::PlayerStrategy> playerStrategy;

public:
    Player(CommonEnum::Symbol symbol, std::shared_ptr<PlayerStrategies::PlayerStrategy> strategy);
    
    CommonEnum::Symbol getSymbol() const { return symbol; }
    std::shared_ptr<PlayerStrategies::PlayerStrategy> getPlayerStrategy() const { return playerStrategy; }
};

} // namespace Utility 