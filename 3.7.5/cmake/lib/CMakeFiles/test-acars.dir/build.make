# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/jmfriedt/sdr/gr-acars

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmfriedt/sdr/gr-acars/cmake

# Include any dependencies generated for this target.
include lib/CMakeFiles/test-acars.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/test-acars.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/test-acars.dir/flags.make

lib/CMakeFiles/test-acars.dir/test_acars.cc.o: lib/CMakeFiles/test-acars.dir/flags.make
lib/CMakeFiles/test-acars.dir/test_acars.cc.o: ../lib/test_acars.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmfriedt/sdr/gr-acars/cmake/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object lib/CMakeFiles/test-acars.dir/test_acars.cc.o"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test-acars.dir/test_acars.cc.o -c /home/jmfriedt/sdr/gr-acars/lib/test_acars.cc

lib/CMakeFiles/test-acars.dir/test_acars.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-acars.dir/test_acars.cc.i"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmfriedt/sdr/gr-acars/lib/test_acars.cc > CMakeFiles/test-acars.dir/test_acars.cc.i

lib/CMakeFiles/test-acars.dir/test_acars.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-acars.dir/test_acars.cc.s"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmfriedt/sdr/gr-acars/lib/test_acars.cc -o CMakeFiles/test-acars.dir/test_acars.cc.s

lib/CMakeFiles/test-acars.dir/test_acars.cc.o.requires:
.PHONY : lib/CMakeFiles/test-acars.dir/test_acars.cc.o.requires

lib/CMakeFiles/test-acars.dir/test_acars.cc.o.provides: lib/CMakeFiles/test-acars.dir/test_acars.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-acars.dir/build.make lib/CMakeFiles/test-acars.dir/test_acars.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-acars.dir/test_acars.cc.o.provides

lib/CMakeFiles/test-acars.dir/test_acars.cc.o.provides.build: lib/CMakeFiles/test-acars.dir/test_acars.cc.o

lib/CMakeFiles/test-acars.dir/qa_acars.cc.o: lib/CMakeFiles/test-acars.dir/flags.make
lib/CMakeFiles/test-acars.dir/qa_acars.cc.o: ../lib/qa_acars.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmfriedt/sdr/gr-acars/cmake/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object lib/CMakeFiles/test-acars.dir/qa_acars.cc.o"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test-acars.dir/qa_acars.cc.o -c /home/jmfriedt/sdr/gr-acars/lib/qa_acars.cc

lib/CMakeFiles/test-acars.dir/qa_acars.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-acars.dir/qa_acars.cc.i"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jmfriedt/sdr/gr-acars/lib/qa_acars.cc > CMakeFiles/test-acars.dir/qa_acars.cc.i

lib/CMakeFiles/test-acars.dir/qa_acars.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-acars.dir/qa_acars.cc.s"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jmfriedt/sdr/gr-acars/lib/qa_acars.cc -o CMakeFiles/test-acars.dir/qa_acars.cc.s

lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.requires:
.PHONY : lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.requires

lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.provides: lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-acars.dir/build.make lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.provides

lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.provides.build: lib/CMakeFiles/test-acars.dir/qa_acars.cc.o

# Object files for target test-acars
test__acars_OBJECTS = \
"CMakeFiles/test-acars.dir/test_acars.cc.o" \
"CMakeFiles/test-acars.dir/qa_acars.cc.o"

# External object files for target test-acars
test__acars_EXTERNAL_OBJECTS =

lib/test-acars: lib/CMakeFiles/test-acars.dir/test_acars.cc.o
lib/test-acars: lib/CMakeFiles/test-acars.dir/qa_acars.cc.o
lib/test-acars: lib/CMakeFiles/test-acars.dir/build.make
lib/test-acars: /usr/local/lib/libfftw3.a
lib/test-acars: /usr/lib/i386-linux-gnu/libgnuradio-runtime.so
lib/test-acars: /usr/lib/i386-linux-gnu/libgnuradio-pmt.so
lib/test-acars: /usr/lib/i386-linux-gnu/libboost_filesystem.so
lib/test-acars: /usr/lib/i386-linux-gnu/libboost_system.so
lib/test-acars: /usr/lib/i386-linux-gnu/libcppunit.so
lib/test-acars: lib/libgnuradio-acars.so
lib/test-acars: /usr/local/lib/libfftw3.a
lib/test-acars: /usr/lib/i386-linux-gnu/libgnuradio-runtime.so
lib/test-acars: /usr/lib/i386-linux-gnu/libgnuradio-pmt.so
lib/test-acars: /usr/lib/i386-linux-gnu/libboost_filesystem.so
lib/test-acars: /usr/lib/i386-linux-gnu/libboost_system.so
lib/test-acars: lib/CMakeFiles/test-acars.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test-acars"
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-acars.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/test-acars.dir/build: lib/test-acars
.PHONY : lib/CMakeFiles/test-acars.dir/build

lib/CMakeFiles/test-acars.dir/requires: lib/CMakeFiles/test-acars.dir/test_acars.cc.o.requires
lib/CMakeFiles/test-acars.dir/requires: lib/CMakeFiles/test-acars.dir/qa_acars.cc.o.requires
.PHONY : lib/CMakeFiles/test-acars.dir/requires

lib/CMakeFiles/test-acars.dir/clean:
	cd /home/jmfriedt/sdr/gr-acars/cmake/lib && $(CMAKE_COMMAND) -P CMakeFiles/test-acars.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/test-acars.dir/clean

lib/CMakeFiles/test-acars.dir/depend:
	cd /home/jmfriedt/sdr/gr-acars/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmfriedt/sdr/gr-acars /home/jmfriedt/sdr/gr-acars/lib /home/jmfriedt/sdr/gr-acars/cmake /home/jmfriedt/sdr/gr-acars/cmake/lib /home/jmfriedt/sdr/gr-acars/cmake/lib/CMakeFiles/test-acars.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/test-acars.dir/depend

