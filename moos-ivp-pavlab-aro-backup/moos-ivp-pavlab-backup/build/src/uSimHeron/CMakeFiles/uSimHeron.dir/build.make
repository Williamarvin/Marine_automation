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
include src/uSimHeron/CMakeFiles/uSimHeron.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/uSimHeron/CMakeFiles/uSimHeron.dir/compiler_depend.make

# Include the progress variables for this target.
include src/uSimHeron/CMakeFiles/uSimHeron.dir/progress.make

# Include the compile flags for this target's objects.
include src/uSimHeron/CMakeFiles/uSimHeron.dir/flags.make

src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.o: src/uSimHeron/CMakeFiles/uSimHeron.dir/flags.make
src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.o: ../src/uSimHeron/HeronSim.cpp
src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.o: src/uSimHeron/CMakeFiles/uSimHeron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.o -MF CMakeFiles/uSimHeron.dir/HeronSim.cpp.o.d -o CMakeFiles/uSimHeron.dir/HeronSim.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/HeronSim.cpp

src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uSimHeron.dir/HeronSim.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/HeronSim.cpp > CMakeFiles/uSimHeron.dir/HeronSim.cpp.i

src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uSimHeron.dir/HeronSim.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/HeronSim.cpp -o CMakeFiles/uSimHeron.dir/HeronSim.cpp.s

src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o: src/uSimHeron/CMakeFiles/uSimHeron.dir/flags.make
src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o: ../src/uSimHeron/HeronSim_Info.cpp
src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o: src/uSimHeron/CMakeFiles/uSimHeron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o -MF CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o.d -o CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/HeronSim_Info.cpp

src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/HeronSim_Info.cpp > CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.i

src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/HeronSim_Info.cpp -o CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.s

src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.o: src/uSimHeron/CMakeFiles/uSimHeron.dir/flags.make
src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.o: ../src/uSimHeron/main.cpp
src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.o: src/uSimHeron/CMakeFiles/uSimHeron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.o -MF CMakeFiles/uSimHeron.dir/main.cpp.o.d -o CMakeFiles/uSimHeron.dir/main.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/main.cpp

src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uSimHeron.dir/main.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/main.cpp > CMakeFiles/uSimHeron.dir/main.cpp.i

src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uSimHeron.dir/main.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron/main.cpp -o CMakeFiles/uSimHeron.dir/main.cpp.s

# Object files for target uSimHeron
uSimHeron_OBJECTS = \
"CMakeFiles/uSimHeron.dir/HeronSim.cpp.o" \
"CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o" \
"CMakeFiles/uSimHeron.dir/main.cpp.o"

# External object files for target uSimHeron
uSimHeron_EXTERNAL_OBJECTS =

../bin/uSimHeron: src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim.cpp.o
../bin/uSimHeron: src/uSimHeron/CMakeFiles/uSimHeron.dir/HeronSim_Info.cpp.o
../bin/uSimHeron: src/uSimHeron/CMakeFiles/uSimHeron.dir/main.cpp.o
../bin/uSimHeron: src/uSimHeron/CMakeFiles/uSimHeron.dir/build.make
../bin/uSimHeron: /home/orangepi/Documents/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/uSimHeron: /home/orangepi/Documents/moos-ivp/build/MOOS/MOOSGeodesy/lib/libMOOSGeodesy.so
../bin/uSimHeron: ../lib/libsock_util.a
../bin/uSimHeron: src/uSimHeron/CMakeFiles/uSimHeron.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/uSimHeron"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uSimHeron.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/uSimHeron/CMakeFiles/uSimHeron.dir/build: ../bin/uSimHeron
.PHONY : src/uSimHeron/CMakeFiles/uSimHeron.dir/build

src/uSimHeron/CMakeFiles/uSimHeron.dir/clean:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron && $(CMAKE_COMMAND) -P CMakeFiles/uSimHeron.dir/cmake_clean.cmake
.PHONY : src/uSimHeron/CMakeFiles/uSimHeron.dir/clean

src/uSimHeron/CMakeFiles/uSimHeron.dir/depend:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/Documents/moos-ivp-pavlab-aro /home/orangepi/Documents/moos-ivp-pavlab-aro/src/uSimHeron /home/orangepi/Documents/moos-ivp-pavlab-aro/build /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron/CMakeFiles/uSimHeron.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/uSimHeron/CMakeFiles/uSimHeron.dir/depend
