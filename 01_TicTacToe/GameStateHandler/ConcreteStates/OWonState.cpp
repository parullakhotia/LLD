#include "OWonState.hpp"
#include <iostream>

namespace GameStateHandler {
namespace ConcreteStates {

void OWonState::handle(std::shared_ptr<Utility::Player> player) {
    std::cout << "Player O wins!" << std::endl;
}

} // namespace ConcreteStates
} // namespace GameStateHandler 