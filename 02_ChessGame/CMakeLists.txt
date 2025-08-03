cmake_minimum_required(VERSION 3.10)
project(ChessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Add executable
add_executable(chess_game
    main.cpp
    CommonEnum/PieceType.cpp
    CommonEnum/Color.cpp
    Utility/Position.cpp
    Utility/Board.cpp
    Utility/Piece.cpp
    Utility/Player.cpp
    PlayerStrategies/PlayerStrategy.cpp
    PlayerStrategies/ConcreteStrategies/HumanPlayerStrategy.cpp
    PlayerStrategies/ConcreteStrategies/AIPlayerStrategy.cpp
    GameStateHandler/GameState.cpp
    GameStateHandler/Context/GameContext.cpp
    GameStateHandler/ConcreteStates/InProgressState.cpp
    GameStateHandler/ConcreteStates/CheckmateState.cpp
    GameStateHandler/ConcreteStates/StalemateState.cpp
    GameStateHandler/ConcreteStates/DrawState.cpp
    Controller/GameController/ChessGame.cpp
    MoveValidation/MoveValidator.cpp
    MoveValidation/ConcreteValidators/PawnMoveValidator.cpp
    MoveValidation/ConcreteValidators/RookMoveValidator.cpp
    MoveValidation/ConcreteValidators/BishopMoveValidator.cpp
    MoveValidation/ConcreteValidators/QueenMoveValidator.cpp
    MoveValidation/ConcreteValidators/KingMoveValidator.cpp
    MoveValidation/ConcreteValidators/KnightMoveValidator.cpp
)

# Include directories
target_include_directories(chess_game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Install target
install(TARGETS chess_game DESTINATION bin) 