#include "Player.hpp"
#include "PlayerStrategies/PlayerStrategy.hpp"

namespace Utility {

Player::Player(CommonEnum::Symbol symbol, std::shared_ptr<PlayerStrategies::PlayerStrategy> strategy)
    : symbol(symbol), playerStrategy(strategy) {}

} // namespace Utility 