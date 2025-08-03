cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(snake_game
    main.cpp
    CommonEnum/Direction.cpp
    CommonEnum/GameStatus.cpp
    Utility/Position.cpp
    Utility/Board.cpp
    Utility/Snake.cpp
    Utility/Food.cpp
    PlayerStrategies/PlayerStrategy.cpp
    PlayerStrategies/ConcreteStrategies/HumanPlayerStrategy.cpp
    PlayerStrategies/ConcreteStrategies/AIPlayerStrategy.cpp
    GameStateHandler/GameState.cpp
    GameStateHandler/Context/GameContext.cpp
    GameStateHandler/ConcreteStates/InProgressState.cpp
    GameStateHandler/ConcreteStates/GameOverState.cpp
    GameStateHandler/ConcreteStates/PausedState.cpp
    Controller/GameController/SnakeGame.cpp
    CollisionDetection/CollisionDetector.cpp
    CollisionDetection/ConcreteDetectors/WallCollisionDetector.cpp
    CollisionDetection/ConcreteDetectors/SelfCollisionDetector.cpp
    CollisionDetection/ConcreteDetectors/FoodCollisionDetector.cpp
)

# Include directories
target_include_directories(snake_game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Install target
install(TARGETS snake_game DESTINATION bin) 