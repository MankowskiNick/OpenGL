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

# Utility rule file for update_mappings.

# Include any custom commands dependencies for this target.
include lib/GLFW/src/CMakeFiles/update_mappings.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/GLFW/src/CMakeFiles/update_mappings.dir/progress.make

lib/GLFW/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/nick/Documents/git/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd /Users/nick/Documents/git/OpenGL/lib/GLFW/src && /opt/homebrew/Cellar/cmake/3.22.0/bin/cmake -P /Users/nick/Documents/git/OpenGL/lib/GLFW/CMake/GenerateMappings.cmake mappings.h.in mappings.h

update_mappings: lib/GLFW/src/CMakeFiles/update_mappings
update_mappings: lib/GLFW/src/CMakeFiles/update_mappings.dir/build.make
.PHONY : update_mappings

# Rule to build all files generated by this target.
lib/GLFW/src/CMakeFiles/update_mappings.dir/build: update_mappings
.PHONY : lib/GLFW/src/CMakeFiles/update_mappings.dir/build

lib/GLFW/src/CMakeFiles/update_mappings.dir/clean:
	cd /Users/nick/Documents/git/OpenGL/build/lib/GLFW/src && $(CMAKE_COMMAND) -P CMakeFiles/update_mappings.dir/cmake_clean.cmake
.PHONY : lib/GLFW/src/CMakeFiles/update_mappings.dir/clean

lib/GLFW/src/CMakeFiles/update_mappings.dir/depend:
	cd /Users/nick/Documents/git/OpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nick/Documents/git/OpenGL /Users/nick/Documents/git/OpenGL/lib/GLFW/src /Users/nick/Documents/git/OpenGL/build /Users/nick/Documents/git/OpenGL/build/lib/GLFW/src /Users/nick/Documents/git/OpenGL/build/lib/GLFW/src/CMakeFiles/update_mappings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/GLFW/src/CMakeFiles/update_mappings.dir/depend

