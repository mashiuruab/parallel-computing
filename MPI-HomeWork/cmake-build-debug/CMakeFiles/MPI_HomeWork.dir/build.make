# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/mashiur/Downloads/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/mashiur/Downloads/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mashiur/projects/parallel-computing/MPI-HomeWork

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MPI_HomeWork.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MPI_HomeWork.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MPI_HomeWork.dir/flags.make

CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o: CMakeFiles/MPI_HomeWork.dir/flags.make
CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o: ../main_mpi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o -c /home/mashiur/projects/parallel-computing/MPI-HomeWork/main_mpi.cpp

CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mashiur/projects/parallel-computing/MPI-HomeWork/main_mpi.cpp > CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.i

CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mashiur/projects/parallel-computing/MPI-HomeWork/main_mpi.cpp -o CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.s

CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.requires:

.PHONY : CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.requires

CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.provides: CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.requires
	$(MAKE) -f CMakeFiles/MPI_HomeWork.dir/build.make CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.provides.build
.PHONY : CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.provides

CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.provides.build: CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o


# Object files for target MPI_HomeWork
MPI_HomeWork_OBJECTS = \
"CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o"

# External object files for target MPI_HomeWork
MPI_HomeWork_EXTERNAL_OBJECTS =

MPI_HomeWork: CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o
MPI_HomeWork: CMakeFiles/MPI_HomeWork.dir/build.make
MPI_HomeWork: CMakeFiles/MPI_HomeWork.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MPI_HomeWork"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MPI_HomeWork.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MPI_HomeWork.dir/build: MPI_HomeWork

.PHONY : CMakeFiles/MPI_HomeWork.dir/build

CMakeFiles/MPI_HomeWork.dir/requires: CMakeFiles/MPI_HomeWork.dir/main_mpi.cpp.o.requires

.PHONY : CMakeFiles/MPI_HomeWork.dir/requires

CMakeFiles/MPI_HomeWork.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MPI_HomeWork.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MPI_HomeWork.dir/clean

CMakeFiles/MPI_HomeWork.dir/depend:
	cd /home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mashiur/projects/parallel-computing/MPI-HomeWork /home/mashiur/projects/parallel-computing/MPI-HomeWork /home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug /home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug /home/mashiur/projects/parallel-computing/MPI-HomeWork/cmake-build-debug/CMakeFiles/MPI_HomeWork.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MPI_HomeWork.dir/depend

