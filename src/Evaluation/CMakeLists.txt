cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
include_directories(${PARENT_DIR}/MoveGenerator/MoveGenerator)
include_directories(${PARENT_DIR}/MoveGenerator/Objects)
add_library(Evaluation Evaluation.cpp Evaluation.h)