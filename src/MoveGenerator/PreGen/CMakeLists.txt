cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
cmake_path(GET PARENT_DIR PARENT_PATH PARENTPARENT_DIR)
include_directories(${PARENT_DIR}/MoveGenerator ${PARENTPARENT_DIR}/Display)
add_library(PreMoveGen PreMoveGen.cpp PreMoveGen.h)