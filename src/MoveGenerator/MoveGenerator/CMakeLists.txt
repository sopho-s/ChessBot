cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
include_directories(${PARENT_DIR}/Objects)
add_library(MoveGen MoveGen.h MoveGen.cpp)