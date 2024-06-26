cmake_minimum_required (VERSION 3.8)
project(ChessBot LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-w)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

include_directories(MoveGenerator/Objects MoveGenerator/PreGen MoveGenerator/MoveGenerator Display Utilities/Hash)

add_executable(ChessBot main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Setting profiler")
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/PROFILE")
endif()

add_subdirectory(Utilities)

add_subdirectory(Display)

add_subdirectory(MoveGenerator)

target_link_libraries(ChessBot PRIVATE
    MoveGen
    PreMoveGen
    Display
    Board
    PositionInfo
    Hash)
