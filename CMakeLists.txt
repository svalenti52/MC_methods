cmake_minimum_required(VERSION 3.7)
project(MC_methods)

set(CMAKE_CXX_STANDARD 14)

add_executable(CRAPS_ORIG craps_orig.cpp)
add_executable(CRAPS_MCS craps_MCS.cpp)
add_executable(CRAPS_DIST_MCS craps_one_dist_MCS.cpp)
add_executable(PIECEWISE_LINEAR Piecewise_Linear_Density.cpp)
add_executable(SAINT_PETERSBURG saintPetersburg.cpp)
add_executable(PARIS_SALON paris_salon.cpp)
add_executable(POISSON Poisson.cpp)
