# C++ Low Level Design Interview Problems

This directory contains C++ implementations of various Low Level Design (LLD) interview problems, converted from the original Java codebase.

## Structure

The project is organized into separate directories for each problem:

- `01_TicTacToe/` - Tic-Tac-Toe game implementation
- `02_ChessGame/` - Chess game implementation (to be implemented)
- `03_SnakeGame/` - Snake and Food game implementation (to be implemented)
- `04_ParkingLot/` - Parking Lot management system (to be implemented)
- `05_ElevatorSystem/` - Elevator system implementation (to be implemented)
- `06_InventoryManagement/` - Inventory management system (to be implemented)
- `07_CarRental/` - Car rental system (to be implemented)
- `08_VendingMachine/` - Vending machine implementation (to be implemented)
- `09_FileSystem/` - File system implementation (to be implemented)
- `10_LoggingSystem/` - Logging system implementation (to be implemented)
- `11_Splitwise/` - Splitwise-like expense sharing system (to be implemented)
- `12_ATMMachine/` - ATM machine implementation (to be implemented)

## Building

To build all projects:

```bash
mkdir build
cd build
cmake ..
make
```

To build a specific project:

```bash
cd build
make 01_TicTacToe
```

## Running

After building, you can run any of the executables:

```bash
./01_TicTacToe
```

## Design Patterns Used

### Tic-Tac-Toe Implementation

The Tic-Tac-Toe game demonstrates several design patterns:

1. **Strategy Pattern**: Used for different player strategies (HumanPlayerStrategy)
2. **State Pattern**: Used for game state management (InProgressState, XWonState, OWonState, DrawState)
3. **Factory Pattern**: Used for creating game components
4. **Observer Pattern**: Used for game state changes

### Key Components

- **Board**: Manages the game board state and move validation
- **Player**: Represents a player with a strategy
- **PlayerStrategy**: Interface for different player behaviors
- **GameState**: Interface for different game states
- **GameContext**: Manages state transitions
- **TicTacToeGame**: Main game controller

## C++ Features Used

- Modern C++17 features
- Smart pointers (std::shared_ptr, std::unique_ptr)
- RAII principles
- Namespaces for organization
- Virtual functions and polymorphism
- STL containers and algorithms
- Exception handling

## Conversion Notes

The C++ implementation preserves the original Java design patterns while adapting to C++ idioms:

- Java interfaces → C++ pure virtual classes
- Java inheritance → C++ inheritance with virtual functions
- Java generics → C++ templates (where applicable)
- Java collections → STL containers
- Java exceptions → C++ exception handling

## Future Implementations

Each remaining problem will follow similar patterns, adapting the original Java design to C++ while maintaining the core architectural principles. 