cmake_minimum_required (VERSION 3.8)
project(ChessBot LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-w)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

include_directories(MoveGenerator/Objects MoveGenerator/PreGen MoveGenerator/MoveGenerator Display)

add_executable(ChessBot main)

add_subdirectory(Display)

add_subdirectory(MoveGenerator)

target_link_libraries(ChessBot PRIVATE
    PreMoveGen
    MoveGen
    Display
    Board
    PositionInfo)
