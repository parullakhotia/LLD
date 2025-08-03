#include "InProgressState.hpp"

namespace GameStateHandler {
namespace ConcreteStates {

void InProgressState::handle(std::shared_ptr<Utility::Player> player) {
    // Game is in progress, no special handling needed
}

} // namespace ConcreteStates
} // namespace GameStateHandler 