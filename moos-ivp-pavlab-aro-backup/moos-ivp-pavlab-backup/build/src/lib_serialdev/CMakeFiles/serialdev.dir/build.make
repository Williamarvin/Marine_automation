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
include src/lib_serialdev/CMakeFiles/serialdev.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/lib_serialdev/CMakeFiles/serialdev.dir/compiler_depend.make

# Include the progress variables for this target.
include src/lib_serialdev/CMakeFiles/serialdev.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib_serialdev/CMakeFiles/serialdev.dir/flags.make

src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.o: src/lib_serialdev/CMakeFiles/serialdev.dir/flags.make
src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.o: ../src/lib_serialdev/serial_device.cpp
src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.o: src/lib_serialdev/CMakeFiles/serialdev.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.o -MF CMakeFiles/serialdev.dir/serial_device.cpp.o.d -o CMakeFiles/serialdev.dir/serial_device.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_serialdev/serial_device.cpp

src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serialdev.dir/serial_device.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_serialdev/serial_device.cpp > CMakeFiles/serialdev.dir/serial_device.cpp.i

src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serialdev.dir/serial_device.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_serialdev/serial_device.cpp -o CMakeFiles/serialdev.dir/serial_device.cpp.s

# Object files for target serialdev
serialdev_OBJECTS = \
"CMakeFiles/serialdev.dir/serial_device.cpp.o"

# External object files for target serialdev
serialdev_EXTERNAL_OBJECTS =

../lib/libserialdev.a: src/lib_serialdev/CMakeFiles/serialdev.dir/serial_device.cpp.o
../lib/libserialdev.a: src/lib_serialdev/CMakeFiles/serialdev.dir/build.make
../lib/libserialdev.a: src/lib_serialdev/CMakeFiles/serialdev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libserialdev.a"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev && $(CMAKE_COMMAND) -P CMakeFiles/serialdev.dir/cmake_clean_target.cmake
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serialdev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib_serialdev/CMakeFiles/serialdev.dir/build: ../lib/libserialdev.a
.PHONY : src/lib_serialdev/CMakeFiles/serialdev.dir/build

src/lib_serialdev/CMakeFiles/serialdev.dir/clean:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev && $(CMAKE_COMMAND) -P CMakeFiles/serialdev.dir/cmake_clean.cmake
.PHONY : src/lib_serialdev/CMakeFiles/serialdev.dir/clean

src/lib_serialdev/CMakeFiles/serialdev.dir/depend:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/Documents/moos-ivp-pavlab-aro /home/orangepi/Documents/moos-ivp-pavlab-aro/src/lib_serialdev /home/orangepi/Documents/moos-ivp-pavlab-aro/build /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev/CMakeFiles/serialdev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib_serialdev/CMakeFiles/serialdev.dir/depend
