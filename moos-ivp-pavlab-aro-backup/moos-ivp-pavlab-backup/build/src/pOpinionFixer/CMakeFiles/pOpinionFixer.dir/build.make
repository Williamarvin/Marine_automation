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
include src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/progress.make

# Include the compile flags for this target's objects.
include src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/flags.make

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/flags.make
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o: ../src/pOpinionFixer/OpinionFixer.cpp
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o -MF CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o.d -o CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/OpinionFixer.cpp

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/OpinionFixer.cpp > CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.i

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/OpinionFixer.cpp -o CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.s

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/flags.make
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o: ../src/pOpinionFixer/OpinionFixer_Info.cpp
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o -MF CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o.d -o CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/OpinionFixer_Info.cpp

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/OpinionFixer_Info.cpp > CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.i

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/OpinionFixer_Info.cpp -o CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.s

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.o: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/flags.make
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.o: ../src/pOpinionFixer/main.cpp
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.o: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.o"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.o -MF CMakeFiles/pOpinionFixer.dir/main.cpp.o.d -o CMakeFiles/pOpinionFixer.dir/main.cpp.o -c /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/main.cpp

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOpinionFixer.dir/main.cpp.i"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/main.cpp > CMakeFiles/pOpinionFixer.dir/main.cpp.i

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOpinionFixer.dir/main.cpp.s"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer/main.cpp -o CMakeFiles/pOpinionFixer.dir/main.cpp.s

# Object files for target pOpinionFixer
pOpinionFixer_OBJECTS = \
"CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o" \
"CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o" \
"CMakeFiles/pOpinionFixer.dir/main.cpp.o"

# External object files for target pOpinionFixer
pOpinionFixer_EXTERNAL_OBJECTS =

../bin/pOpinionFixer: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer.cpp.o
../bin/pOpinionFixer: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/OpinionFixer_Info.cpp.o
../bin/pOpinionFixer: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/main.cpp.o
../bin/pOpinionFixer: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/build.make
../bin/pOpinionFixer: /home/orangepi/Documents/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/pOpinionFixer: src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/Documents/moos-ivp-pavlab-aro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/pOpinionFixer"
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pOpinionFixer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/build: ../bin/pOpinionFixer
.PHONY : src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/build

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/clean:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer && $(CMAKE_COMMAND) -P CMakeFiles/pOpinionFixer.dir/cmake_clean.cmake
.PHONY : src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/clean

src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/depend:
	cd /home/orangepi/Documents/moos-ivp-pavlab-aro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/Documents/moos-ivp-pavlab-aro /home/orangepi/Documents/moos-ivp-pavlab-aro/src/pOpinionFixer /home/orangepi/Documents/moos-ivp-pavlab-aro/build /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer /home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pOpinionFixer/CMakeFiles/pOpinionFixer.dir/depend
