cmake_minimum_required(VERSION 3.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Module1_Prj)

add_subdirectory(calcLib)

add_executable(Module1_App main.cpp)

target_link_libraries(Module1_App PUBLIC calcLib)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Module1_App PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/calcLib")
                          