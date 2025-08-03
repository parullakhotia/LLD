#include "XWonState.hpp"
#include <iostream>

namespace GameStateHandler {
namespace ConcreteStates {

void XWonState::handle(std::shared_ptr<Utility::Player> player) {
    std::cout << "Player X wins!" << std::endl;
}

} // namespace ConcreteStates
} // namespace GameStateHandler 