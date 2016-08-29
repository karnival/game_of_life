add_executable(game_of_life main.cpp grid.cpp cell.cpp util.cpp)
target_link_libraries(game_of_life ${Boost_LIBRARIES})
