# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /mnt/f/FinalProject/code/SDK/example/example_nv12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/f/FinalProject/code/SDK/example/example_nv12/build

# Include any dependencies generated for this target.
include CMakeFiles/ovision_enhance_exp1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ovision_enhance_exp1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ovision_enhance_exp1.dir/flags.make

CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.o: CMakeFiles/ovision_enhance_exp1.dir/flags.make
CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.o: ../project_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/f/FinalProject/code/SDK/example/example_nv12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.o -c /mnt/f/FinalProject/code/SDK/example/example_nv12/project_main.cpp

CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/f/FinalProject/code/SDK/example/example_nv12/project_main.cpp > CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.i

CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/f/FinalProject/code/SDK/example/example_nv12/project_main.cpp -o CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.s

# Object files for target ovision_enhance_exp1
ovision_enhance_exp1_OBJECTS = \
"CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.o"

# External object files for target ovision_enhance_exp1
ovision_enhance_exp1_EXTERNAL_OBJECTS =

ovision_enhance_exp1: CMakeFiles/ovision_enhance_exp1.dir/project_main.cpp.o
ovision_enhance_exp1: CMakeFiles/ovision_enhance_exp1.dir/build.make
ovision_enhance_exp1: CMakeFiles/ovision_enhance_exp1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/f/FinalProject/code/SDK/example/example_nv12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ovision_enhance_exp1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ovision_enhance_exp1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ovision_enhance_exp1.dir/build: ovision_enhance_exp1

.PHONY : CMakeFiles/ovision_enhance_exp1.dir/build

CMakeFiles/ovision_enhance_exp1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ovision_enhance_exp1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ovision_enhance_exp1.dir/clean

CMakeFiles/ovision_enhance_exp1.dir/depend:
	cd /mnt/f/FinalProject/code/SDK/example/example_nv12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/f/FinalProject/code/SDK/example/example_nv12 /mnt/f/FinalProject/code/SDK/example/example_nv12 /mnt/f/FinalProject/code/SDK/example/example_nv12/build /mnt/f/FinalProject/code/SDK/example/example_nv12/build /mnt/f/FinalProject/code/SDK/example/example_nv12/build/CMakeFiles/ovision_enhance_exp1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ovision_enhance_exp1.dir/depend

