# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/Cpp-For-C-Programmers/module_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/Cpp-For-C-Programmers/module_1/build

# Include any dependencies generated for this target.
include CMakeFiles/Module1_App.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Module1_App.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Module1_App.dir/flags.make

CMakeFiles/Module1_App.dir/main.cpp.o: CMakeFiles/Module1_App.dir/flags.make
CMakeFiles/Module1_App.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/Cpp-For-C-Programmers/module_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Module1_App.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Module1_App.dir/main.cpp.o -c /workspaces/Cpp-For-C-Programmers/module_1/main.cpp

CMakeFiles/Module1_App.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Module1_App.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/Cpp-For-C-Programmers/module_1/main.cpp > CMakeFiles/Module1_App.dir/main.cpp.i

CMakeFiles/Module1_App.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Module1_App.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/Cpp-For-C-Programmers/module_1/main.cpp -o CMakeFiles/Module1_App.dir/main.cpp.s

# Object files for target Module1_App
Module1_App_OBJECTS = \
"CMakeFiles/Module1_App.dir/main.cpp.o"

# External object files for target Module1_App
Module1_App_EXTERNAL_OBJECTS =

Module1_App: CMakeFiles/Module1_App.dir/main.cpp.o
Module1_App: CMakeFiles/Module1_App.dir/build.make
Module1_App: CMakeFiles/Module1_App.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/Cpp-For-C-Programmers/module_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Module1_App"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Module1_App.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Module1_App.dir/build: Module1_App

.PHONY : CMakeFiles/Module1_App.dir/build

CMakeFiles/Module1_App.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Module1_App.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Module1_App.dir/clean

CMakeFiles/Module1_App.dir/depend:
	cd /workspaces/Cpp-For-C-Programmers/module_1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/Cpp-For-C-Programmers/module_1 /workspaces/Cpp-For-C-Programmers/module_1 /workspaces/Cpp-For-C-Programmers/module_1/build /workspaces/Cpp-For-C-Programmers/module_1/build /workspaces/Cpp-For-C-Programmers/module_1/build/CMakeFiles/Module1_App.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Module1_App.dir/depend

