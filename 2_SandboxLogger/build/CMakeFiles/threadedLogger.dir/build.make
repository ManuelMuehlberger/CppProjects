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
CMAKE_SOURCE_DIR = /Users/manu/Downloads/HW12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/manu/Downloads/HW12/build

# Include any dependencies generated for this target.
include CMakeFiles/threadedLogger.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/threadedLogger.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/threadedLogger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threadedLogger.dir/flags.make

CMakeFiles/threadedLogger.dir/main.cpp.o: CMakeFiles/threadedLogger.dir/flags.make
CMakeFiles/threadedLogger.dir/main.cpp.o: ../main.cpp
CMakeFiles/threadedLogger.dir/main.cpp.o: CMakeFiles/threadedLogger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/manu/Downloads/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threadedLogger.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/threadedLogger.dir/main.cpp.o -MF CMakeFiles/threadedLogger.dir/main.cpp.o.d -o CMakeFiles/threadedLogger.dir/main.cpp.o -c /Users/manu/Downloads/HW12/main.cpp

CMakeFiles/threadedLogger.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadedLogger.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/manu/Downloads/HW12/main.cpp > CMakeFiles/threadedLogger.dir/main.cpp.i

CMakeFiles/threadedLogger.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadedLogger.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/manu/Downloads/HW12/main.cpp -o CMakeFiles/threadedLogger.dir/main.cpp.s

# Object files for target threadedLogger
threadedLogger_OBJECTS = \
"CMakeFiles/threadedLogger.dir/main.cpp.o"

# External object files for target threadedLogger
threadedLogger_EXTERNAL_OBJECTS =

threadedLogger: CMakeFiles/threadedLogger.dir/main.cpp.o
threadedLogger: CMakeFiles/threadedLogger.dir/build.make
threadedLogger: liblibThreadedLogger.a
threadedLogger: CMakeFiles/threadedLogger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/manu/Downloads/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threadedLogger"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadedLogger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threadedLogger.dir/build: threadedLogger
.PHONY : CMakeFiles/threadedLogger.dir/build

CMakeFiles/threadedLogger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threadedLogger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threadedLogger.dir/clean

CMakeFiles/threadedLogger.dir/depend:
	cd /Users/manu/Downloads/HW12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/manu/Downloads/HW12 /Users/manu/Downloads/HW12 /Users/manu/Downloads/HW12/build /Users/manu/Downloads/HW12/build /Users/manu/Downloads/HW12/build/CMakeFiles/threadedLogger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threadedLogger.dir/depend
