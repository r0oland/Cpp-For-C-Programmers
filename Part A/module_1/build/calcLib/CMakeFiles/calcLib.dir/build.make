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
include calcLib/CMakeFiles/calcLib.dir/depend.make

# Include the progress variables for this target.
include calcLib/CMakeFiles/calcLib.dir/progress.make

# Include the compile flags for this target's objects.
include calcLib/CMakeFiles/calcLib.dir/flags.make

calcLib/CMakeFiles/calcLib.dir/calc.cpp.o: calcLib/CMakeFiles/calcLib.dir/flags.make
calcLib/CMakeFiles/calcLib.dir/calc.cpp.o: ../calcLib/calc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/Cpp-For-C-Programmers/module_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object calcLib/CMakeFiles/calcLib.dir/calc.cpp.o"
	cd /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calcLib.dir/calc.cpp.o -c /workspaces/Cpp-For-C-Programmers/module_1/calcLib/calc.cpp

calcLib/CMakeFiles/calcLib.dir/calc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calcLib.dir/calc.cpp.i"
	cd /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/Cpp-For-C-Programmers/module_1/calcLib/calc.cpp > CMakeFiles/calcLib.dir/calc.cpp.i

calcLib/CMakeFiles/calcLib.dir/calc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calcLib.dir/calc.cpp.s"
	cd /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/Cpp-For-C-Programmers/module_1/calcLib/calc.cpp -o CMakeFiles/calcLib.dir/calc.cpp.s

# Object files for target calcLib
calcLib_OBJECTS = \
"CMakeFiles/calcLib.dir/calc.cpp.o"

# External object files for target calcLib
calcLib_EXTERNAL_OBJECTS =

calcLib/libcalcLib.a: calcLib/CMakeFiles/calcLib.dir/calc.cpp.o
calcLib/libcalcLib.a: calcLib/CMakeFiles/calcLib.dir/build.make
calcLib/libcalcLib.a: calcLib/CMakeFiles/calcLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/Cpp-For-C-Programmers/module_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcalcLib.a"
	cd /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib && $(CMAKE_COMMAND) -P CMakeFiles/calcLib.dir/cmake_clean_target.cmake
	cd /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calcLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
calcLib/CMakeFiles/calcLib.dir/build: calcLib/libcalcLib.a

.PHONY : calcLib/CMakeFiles/calcLib.dir/build

calcLib/CMakeFiles/calcLib.dir/clean:
	cd /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib && $(CMAKE_COMMAND) -P CMakeFiles/calcLib.dir/cmake_clean.cmake
.PHONY : calcLib/CMakeFiles/calcLib.dir/clean

calcLib/CMakeFiles/calcLib.dir/depend:
	cd /workspaces/Cpp-For-C-Programmers/module_1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/Cpp-For-C-Programmers/module_1 /workspaces/Cpp-For-C-Programmers/module_1/calcLib /workspaces/Cpp-For-C-Programmers/module_1/build /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib /workspaces/Cpp-For-C-Programmers/module_1/build/calcLib/CMakeFiles/calcLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : calcLib/CMakeFiles/calcLib.dir/depend

