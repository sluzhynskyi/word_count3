# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/oem/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/oem/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oem/Documents/AcsProjects/word_count3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oem/Documents/AcsProjects/word_count3/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/word_count.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/word_count.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/word_count.dir/flags.make

CMakeFiles/word_count.dir/src/main.cpp.o: CMakeFiles/word_count.dir/flags.make
CMakeFiles/word_count.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oem/Documents/AcsProjects/word_count3/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/word_count.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/word_count.dir/src/main.cpp.o -c /home/oem/Documents/AcsProjects/word_count3/src/main.cpp

CMakeFiles/word_count.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/word_count.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oem/Documents/AcsProjects/word_count3/src/main.cpp > CMakeFiles/word_count.dir/src/main.cpp.i

CMakeFiles/word_count.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/word_count.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oem/Documents/AcsProjects/word_count3/src/main.cpp -o CMakeFiles/word_count.dir/src/main.cpp.s

CMakeFiles/word_count.dir/lib/read_write.cpp.o: CMakeFiles/word_count.dir/flags.make
CMakeFiles/word_count.dir/lib/read_write.cpp.o: ../lib/read_write.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oem/Documents/AcsProjects/word_count3/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/word_count.dir/lib/read_write.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/word_count.dir/lib/read_write.cpp.o -c /home/oem/Documents/AcsProjects/word_count3/lib/read_write.cpp

CMakeFiles/word_count.dir/lib/read_write.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/word_count.dir/lib/read_write.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oem/Documents/AcsProjects/word_count3/lib/read_write.cpp > CMakeFiles/word_count.dir/lib/read_write.cpp.i

CMakeFiles/word_count.dir/lib/read_write.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/word_count.dir/lib/read_write.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oem/Documents/AcsProjects/word_count3/lib/read_write.cpp -o CMakeFiles/word_count.dir/lib/read_write.cpp.s

# Object files for target word_count
word_count_OBJECTS = \
"CMakeFiles/word_count.dir/src/main.cpp.o" \
"CMakeFiles/word_count.dir/lib/read_write.cpp.o"

# External object files for target word_count
word_count_EXTERNAL_OBJECTS =

word_count: CMakeFiles/word_count.dir/src/main.cpp.o
word_count: CMakeFiles/word_count.dir/lib/read_write.cpp.o
word_count: CMakeFiles/word_count.dir/build.make
word_count: /usr/lib/x86_64-linux-gnu/libicuuc.so
word_count: /usr/lib/x86_64-linux-gnu/libicui18n.so
word_count: /usr/lib/x86_64-linux-gnu/libtbb.so.2
word_count: /usr/lib/x86_64-linux-gnu/libboost_locale.so.1.71.0
word_count: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
word_count: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
word_count: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
word_count: /usr/lib/x86_64-linux-gnu/libarchive.so
word_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
word_count: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
word_count: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
word_count: CMakeFiles/word_count.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oem/Documents/AcsProjects/word_count3/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable word_count"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/word_count.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/word_count.dir/build: word_count

.PHONY : CMakeFiles/word_count.dir/build

CMakeFiles/word_count.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/word_count.dir/cmake_clean.cmake
.PHONY : CMakeFiles/word_count.dir/clean

CMakeFiles/word_count.dir/depend:
	cd /home/oem/Documents/AcsProjects/word_count3/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oem/Documents/AcsProjects/word_count3 /home/oem/Documents/AcsProjects/word_count3 /home/oem/Documents/AcsProjects/word_count3/cmake-build-release /home/oem/Documents/AcsProjects/word_count3/cmake-build-release /home/oem/Documents/AcsProjects/word_count3/cmake-build-release/CMakeFiles/word_count.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/word_count.dir/depend

