#pragma once

#include "PlayerStrategies/PlayerStrategy.hpp"
#include <string>

namespace PlayerStrategies {
namespace ConcreteStrategies {

class HumanPlayerStrategy : public PlayerStrategy {
private:
    std::string playerName;

public:
    explicit HumanPlayerStrategy(const std::string& playerName);
    Utility::Position makeMove(const std::shared_ptr<Utility::Board>& board) override;
};

} // namespace ConcreteStrategies
} // namespace PlayerStrategies 