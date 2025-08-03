#include "DrawState.hpp"
#include <iostream>

namespace GameStateHandler {
namespace ConcreteStates {

void DrawState::handle(std::shared_ptr<Utility::Player> player) {
    std::cout << "It's a draw!" << std::endl;
}

} // namespace ConcreteStates
} // namespace GameStateHandler 