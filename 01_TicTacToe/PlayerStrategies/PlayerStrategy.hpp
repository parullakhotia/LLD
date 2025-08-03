#pragma once

#include <memory>

// Forward declaration
namespace Utility {
    class Board;
    class Position;
}

namespace PlayerStrategies {

class PlayerStrategy {
public:
    virtual ~PlayerStrategy() = default;
    virtual Utility::Position makeMove(const std::shared_ptr<Utility::Board>& board) = 0;
};

} // namespace PlayerStrategies 