# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jojo/Documents/Project/PS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jojo/Documents/Project/PS/build

# Include any dependencies generated for this target.
include CMakeFiles/Test01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Test01.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Test01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test01.dir/flags.make

CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o: CMakeFiles/Test01.dir/flags.make
CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o: ../tests/01-hello-world.cpp
CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o: CMakeFiles/Test01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jojo/Documents/Project/PS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o -MF CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o.d -o CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o -c /home/jojo/Documents/Project/PS/tests/01-hello-world.cpp

CMakeFiles/Test01.dir/tests/01-hello-world.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test01.dir/tests/01-hello-world.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jojo/Documents/Project/PS/tests/01-hello-world.cpp > CMakeFiles/Test01.dir/tests/01-hello-world.cpp.i

CMakeFiles/Test01.dir/tests/01-hello-world.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test01.dir/tests/01-hello-world.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jojo/Documents/Project/PS/tests/01-hello-world.cpp -o CMakeFiles/Test01.dir/tests/01-hello-world.cpp.s

# Object files for target Test01
Test01_OBJECTS = \
"CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o"

# External object files for target Test01
Test01_EXTERNAL_OBJECTS =

Test01: CMakeFiles/Test01.dir/tests/01-hello-world.cpp.o
Test01: CMakeFiles/Test01.dir/build.make
Test01: libGraphLibrary.a
Test01: CMakeFiles/Test01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jojo/Documents/Project/PS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Test01.dir/build: Test01
.PHONY : CMakeFiles/Test01.dir/build

CMakeFiles/Test01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test01.dir/clean

CMakeFiles/Test01.dir/depend:
	cd /home/jojo/Documents/Project/PS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jojo/Documents/Project/PS /home/jojo/Documents/Project/PS /home/jojo/Documents/Project/PS/build /home/jojo/Documents/Project/PS/build /home/jojo/Documents/Project/PS/build/CMakeFiles/Test01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Test01.dir/depend

