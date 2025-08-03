cmake_minimum_required(VERSION 3.16)
project(LLDInterviewProblems VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add subdirectories for different problems
add_subdirectory(01_TicTacToe)
add_subdirectory(02_ChessGame)
add_subdirectory(03_SnakeGame)
add_subdirectory(04_ParkingLot)
add_subdirectory(05_ElevatorSystem)
add_subdirectory(06_InventoryManagement)
add_subdirectory(07_CarRental)
add_subdirectory(08_VendingMachine)
add_subdirectory(09_FileSystem)
add_subdirectory(10_LoggingSystem)
add_subdirectory(11_Splitwise)
add_subdirectory(12_ATMMachine)

# Install target
install(TARGETS 
    01_TicTacToe
    02_ChessGame
    03_SnakeGame
    04_ParkingLot
    05_ElevatorSystem
    06_InventoryManagement
    07_CarRental
    08_VendingMachine
    09_FileSystem
    10_LoggingSystem
    11_Splitwise
    12_ATMMachine
    DESTINATION bin
) 