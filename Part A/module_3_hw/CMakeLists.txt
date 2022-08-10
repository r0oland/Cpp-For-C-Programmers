cmake_minimum_required(VERSION 3.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Module3_Prj)

add_executable(Module3_App main.cpp)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Module3_App PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )
                          