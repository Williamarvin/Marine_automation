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
include src/lib_sock_utils/CMakeFiles/sock_util.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/lib_sock_utils/CMakeFiles/sock_util.dir/compiler_depend.make

# Include the progress variables for this target.
include src/lib_sock_utils/CMakeFiles/sock_util.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib_sock_utils/CMakeFiles/sock_util.dir/flags.make

src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.o: src/lib_sock_utils/CMakeFiles/sock_util.dir/flags.make
src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.o: ../src/lib_sock_utils/SockNinja.cpp
src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.o: src/lib_sock_utils/CMakeFiles/sock_util.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.o -MF CMakeFiles/sock_util.dir/SockNinja.cpp.o.d -o CMakeFiles/sock_util.dir/SockNinja.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_sock_utils/SockNinja.cpp

src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sock_util.dir/SockNinja.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_sock_utils/SockNinja.cpp > CMakeFiles/sock_util.dir/SockNinja.cpp.i

src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sock_util.dir/SockNinja.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_sock_utils/SockNinja.cpp -o CMakeFiles/sock_util.dir/SockNinja.cpp.s

# Object files for target sock_util
sock_util_OBJECTS = \
"CMakeFiles/sock_util.dir/SockNinja.cpp.o"

# External object files for target sock_util
sock_util_EXTERNAL_OBJECTS =

../lib/libsock_util.a: src/lib_sock_utils/CMakeFiles/sock_util.dir/SockNinja.cpp.o
../lib/libsock_util.a: src/lib_sock_utils/CMakeFiles/sock_util.dir/build.make
../lib/libsock_util.a: src/lib_sock_utils/CMakeFiles/sock_util.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libsock_util.a"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils && $(CMAKE_COMMAND) -P CMakeFiles/sock_util.dir/cmake_clean_target.cmake
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sock_util.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib_sock_utils/CMakeFiles/sock_util.dir/build: ../lib/libsock_util.a
.PHONY : src/lib_sock_utils/CMakeFiles/sock_util.dir/build

src/lib_sock_utils/CMakeFiles/sock_util.dir/clean:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils && $(CMAKE_COMMAND) -P CMakeFiles/sock_util.dir/cmake_clean.cmake
.PHONY : src/lib_sock_utils/CMakeFiles/sock_util.dir/clean

src/lib_sock_utils/CMakeFiles/sock_util.dir/depend:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/Documents/moos-ivp-pavlab-aro /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_sock_utils /home/orangepi/Documents/moos-ivp-pavlab-aro/build /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils/CMakeFiles/sock_util.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib_sock_utils/CMakeFiles/sock_util.dir/depend

