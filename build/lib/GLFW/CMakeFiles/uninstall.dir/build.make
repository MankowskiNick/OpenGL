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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.22.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.22.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nick/Documents/git/OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nick/Documents/git/OpenGL/build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include lib/GLFW/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/GLFW/CMakeFiles/uninstall.dir/progress.make

lib/GLFW/CMakeFiles/uninstall:
	cd /Users/nick/Documents/git/OpenGL/build/lib/GLFW && /opt/homebrew/Cellar/cmake/3.22.0/bin/cmake -P /Users/nick/Documents/git/OpenGL/build/lib/GLFW/cmake_uninstall.cmake

uninstall: lib/GLFW/CMakeFiles/uninstall
uninstall: lib/GLFW/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
lib/GLFW/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : lib/GLFW/CMakeFiles/uninstall.dir/build

lib/GLFW/CMakeFiles/uninstall.dir/clean:
	cd /Users/nick/Documents/git/OpenGL/build/lib/GLFW && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : lib/GLFW/CMakeFiles/uninstall.dir/clean

lib/GLFW/CMakeFiles/uninstall.dir/depend:
	cd /Users/nick/Documents/git/OpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nick/Documents/git/OpenGL /Users/nick/Documents/git/OpenGL/lib/GLFW /Users/nick/Documents/git/OpenGL/build /Users/nick/Documents/git/OpenGL/build/lib/GLFW /Users/nick/Documents/git/OpenGL/build/lib/GLFW/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/GLFW/CMakeFiles/uninstall.dir/depend

