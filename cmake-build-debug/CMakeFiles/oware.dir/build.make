# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/FEUP/prog/oware

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/FEUP/prog/oware/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/oware.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/oware.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oware.dir/flags.make

CMakeFiles/oware.dir/src/main.cpp.o: CMakeFiles/oware.dir/flags.make
CMakeFiles/oware.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/FEUP/prog/oware/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/oware.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/oware.dir/src/main.cpp.o -c /mnt/c/FEUP/prog/oware/src/main.cpp

CMakeFiles/oware.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oware.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/FEUP/prog/oware/src/main.cpp > CMakeFiles/oware.dir/src/main.cpp.i

CMakeFiles/oware.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oware.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/FEUP/prog/oware/src/main.cpp -o CMakeFiles/oware.dir/src/main.cpp.s

CMakeFiles/oware.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/oware.dir/src/main.cpp.o.requires

CMakeFiles/oware.dir/src/main.cpp.o.provides: CMakeFiles/oware.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/oware.dir/build.make CMakeFiles/oware.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/oware.dir/src/main.cpp.o.provides

CMakeFiles/oware.dir/src/main.cpp.o.provides.build: CMakeFiles/oware.dir/src/main.cpp.o


CMakeFiles/oware.dir/src/Board.cpp.o: CMakeFiles/oware.dir/flags.make
CMakeFiles/oware.dir/src/Board.cpp.o: ../src/Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/FEUP/prog/oware/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/oware.dir/src/Board.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/oware.dir/src/Board.cpp.o -c /mnt/c/FEUP/prog/oware/src/Board.cpp

CMakeFiles/oware.dir/src/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oware.dir/src/Board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/FEUP/prog/oware/src/Board.cpp > CMakeFiles/oware.dir/src/Board.cpp.i

CMakeFiles/oware.dir/src/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oware.dir/src/Board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/FEUP/prog/oware/src/Board.cpp -o CMakeFiles/oware.dir/src/Board.cpp.s

CMakeFiles/oware.dir/src/Board.cpp.o.requires:

.PHONY : CMakeFiles/oware.dir/src/Board.cpp.o.requires

CMakeFiles/oware.dir/src/Board.cpp.o.provides: CMakeFiles/oware.dir/src/Board.cpp.o.requires
	$(MAKE) -f CMakeFiles/oware.dir/build.make CMakeFiles/oware.dir/src/Board.cpp.o.provides.build
.PHONY : CMakeFiles/oware.dir/src/Board.cpp.o.provides

CMakeFiles/oware.dir/src/Board.cpp.o.provides.build: CMakeFiles/oware.dir/src/Board.cpp.o


CMakeFiles/oware.dir/src/Player.cpp.o: CMakeFiles/oware.dir/flags.make
CMakeFiles/oware.dir/src/Player.cpp.o: ../src/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/FEUP/prog/oware/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/oware.dir/src/Player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/oware.dir/src/Player.cpp.o -c /mnt/c/FEUP/prog/oware/src/Player.cpp

CMakeFiles/oware.dir/src/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oware.dir/src/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/FEUP/prog/oware/src/Player.cpp > CMakeFiles/oware.dir/src/Player.cpp.i

CMakeFiles/oware.dir/src/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oware.dir/src/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/FEUP/prog/oware/src/Player.cpp -o CMakeFiles/oware.dir/src/Player.cpp.s

CMakeFiles/oware.dir/src/Player.cpp.o.requires:

.PHONY : CMakeFiles/oware.dir/src/Player.cpp.o.requires

CMakeFiles/oware.dir/src/Player.cpp.o.provides: CMakeFiles/oware.dir/src/Player.cpp.o.requires
	$(MAKE) -f CMakeFiles/oware.dir/build.make CMakeFiles/oware.dir/src/Player.cpp.o.provides.build
.PHONY : CMakeFiles/oware.dir/src/Player.cpp.o.provides

CMakeFiles/oware.dir/src/Player.cpp.o.provides.build: CMakeFiles/oware.dir/src/Player.cpp.o


# Object files for target oware
oware_OBJECTS = \
"CMakeFiles/oware.dir/src/main.cpp.o" \
"CMakeFiles/oware.dir/src/Board.cpp.o" \
"CMakeFiles/oware.dir/src/Player.cpp.o"

# External object files for target oware
oware_EXTERNAL_OBJECTS =

oware: CMakeFiles/oware.dir/src/main.cpp.o
oware: CMakeFiles/oware.dir/src/Board.cpp.o
oware: CMakeFiles/oware.dir/src/Player.cpp.o
oware: CMakeFiles/oware.dir/build.make
oware: CMakeFiles/oware.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/FEUP/prog/oware/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable oware"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oware.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oware.dir/build: oware

.PHONY : CMakeFiles/oware.dir/build

CMakeFiles/oware.dir/requires: CMakeFiles/oware.dir/src/main.cpp.o.requires
CMakeFiles/oware.dir/requires: CMakeFiles/oware.dir/src/Board.cpp.o.requires
CMakeFiles/oware.dir/requires: CMakeFiles/oware.dir/src/Player.cpp.o.requires

.PHONY : CMakeFiles/oware.dir/requires

CMakeFiles/oware.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/oware.dir/cmake_clean.cmake
.PHONY : CMakeFiles/oware.dir/clean

CMakeFiles/oware.dir/depend:
	cd /mnt/c/FEUP/prog/oware/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/FEUP/prog/oware /mnt/c/FEUP/prog/oware /mnt/c/FEUP/prog/oware/cmake-build-debug /mnt/c/FEUP/prog/oware/cmake-build-debug /mnt/c/FEUP/prog/oware/cmake-build-debug/CMakeFiles/oware.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/oware.dir/depend

