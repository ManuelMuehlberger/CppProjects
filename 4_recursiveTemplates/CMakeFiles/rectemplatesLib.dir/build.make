# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/manu/Downloads/CppProjects/4_recursiveTemplates

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/manu/Downloads/CppProjects/4_recursiveTemplates

# Include any dependencies generated for this target.
include CMakeFiles/rectemplatesLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rectemplatesLib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rectemplatesLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rectemplatesLib.dir/flags.make

CMakeFiles/rectemplatesLib.dir/main.cpp.o: CMakeFiles/rectemplatesLib.dir/flags.make
CMakeFiles/rectemplatesLib.dir/main.cpp.o: main.cpp
CMakeFiles/rectemplatesLib.dir/main.cpp.o: CMakeFiles/rectemplatesLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/manu/Downloads/CppProjects/4_recursiveTemplates/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rectemplatesLib.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rectemplatesLib.dir/main.cpp.o -MF CMakeFiles/rectemplatesLib.dir/main.cpp.o.d -o CMakeFiles/rectemplatesLib.dir/main.cpp.o -c /Users/manu/Downloads/CppProjects/4_recursiveTemplates/main.cpp

CMakeFiles/rectemplatesLib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rectemplatesLib.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/manu/Downloads/CppProjects/4_recursiveTemplates/main.cpp > CMakeFiles/rectemplatesLib.dir/main.cpp.i

CMakeFiles/rectemplatesLib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rectemplatesLib.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/manu/Downloads/CppProjects/4_recursiveTemplates/main.cpp -o CMakeFiles/rectemplatesLib.dir/main.cpp.s

# Object files for target rectemplatesLib
rectemplatesLib_OBJECTS = \
"CMakeFiles/rectemplatesLib.dir/main.cpp.o"

# External object files for target rectemplatesLib
rectemplatesLib_EXTERNAL_OBJECTS =

librectemplatesLib.a: CMakeFiles/rectemplatesLib.dir/main.cpp.o
librectemplatesLib.a: CMakeFiles/rectemplatesLib.dir/build.make
librectemplatesLib.a: CMakeFiles/rectemplatesLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/manu/Downloads/CppProjects/4_recursiveTemplates/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librectemplatesLib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/rectemplatesLib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rectemplatesLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rectemplatesLib.dir/build: librectemplatesLib.a
.PHONY : CMakeFiles/rectemplatesLib.dir/build

CMakeFiles/rectemplatesLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rectemplatesLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rectemplatesLib.dir/clean

CMakeFiles/rectemplatesLib.dir/depend:
	cd /Users/manu/Downloads/CppProjects/4_recursiveTemplates && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/manu/Downloads/CppProjects/4_recursiveTemplates /Users/manu/Downloads/CppProjects/4_recursiveTemplates /Users/manu/Downloads/CppProjects/4_recursiveTemplates /Users/manu/Downloads/CppProjects/4_recursiveTemplates /Users/manu/Downloads/CppProjects/4_recursiveTemplates/CMakeFiles/rectemplatesLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rectemplatesLib.dir/depend

