add_executable(test test.cpp ${PROJECT_SOURCE_DIR}/src/grid.cpp ${PROJECT_SOURCE_DIR}/src/cell.cpp ${PROJECT_SOURCE_DIR}/src/util.cpp)
configure_file(${PROJECT_SOURCE_DIR}/test/test_grid.txt ${CMAKE_CURRENT_BINARY_DIR}/test_grid.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test/test_grid_video.txt ${CMAKE_CURRENT_BINARY_DIR}/test_grid_video.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test/test_grid_1024.txt ${CMAKE_CURRENT_BINARY_DIR}/test_grid_1024.txt COPYONLY)
