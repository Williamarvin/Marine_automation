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
CMAKE_SOURCE_DIR = /home/orangepi/Documents/moos-ivp-pavlab-aro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orangepi/Documents/moos-ivp-pavlab-aro/build

# Include any dependencies generated for this target.
include src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/compiler_depend.make

# Include the progress variables for this target.
include src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/flags.make

src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o: src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/flags.make
src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o: ../src/lib_bhv_shell/BHV_Shell.cpp
src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o: src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o -MF CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o.d -o CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_bhv_shell/BHV_Shell.cpp

src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_bhv_shell/BHV_Shell.cpp > CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.i

src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_bhv_shell/BHV_Shell.cpp -o CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.s

# Object files for target BHV_Shell
BHV_Shell_OBJECTS = \
"CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o"

# External object files for target BHV_Shell
BHV_Shell_EXTERNAL_OBJECTS =

../lib/libBHV_Shell.so: src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/BHV_Shell.cpp.o
../lib/libBHV_Shell.so: src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/build.make
../lib/libBHV_Shell.so: src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../../lib/libBHV_Shell.so"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BHV_Shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/build: ../lib/libBHV_Shell.so
.PHONY : src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/build

src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/clean:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell && $(CMAKE_COMMAND) -P CMakeFiles/BHV_Shell.dir/cmake_clean.cmake
.PHONY : src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/clean

src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/depend:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/Documents/moos-ivp-pavlab-aro /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_bhv_shell /home/orangepi/Documents/moos-ivp-pavlab-aro/build /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib_bhv_shell/CMakeFiles/BHV_Shell.dir/depend

