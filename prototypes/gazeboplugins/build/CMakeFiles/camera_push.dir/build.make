# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/samholmes/SEP-CTs/prototypes/gazeboplugins

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samholmes/SEP-CTs/prototypes/gazeboplugins/build

# Include any dependencies generated for this target.
include CMakeFiles/camera_push.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/camera_push.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camera_push.dir/flags.make

CMakeFiles/camera_push.dir/camera_push.cc.o: CMakeFiles/camera_push.dir/flags.make
CMakeFiles/camera_push.dir/camera_push.cc.o: ../camera_push.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/samholmes/SEP-CTs/prototypes/gazeboplugins/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/camera_push.dir/camera_push.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/camera_push.dir/camera_push.cc.o -c /home/samholmes/SEP-CTs/prototypes/gazeboplugins/camera_push.cc

CMakeFiles/camera_push.dir/camera_push.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camera_push.dir/camera_push.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/samholmes/SEP-CTs/prototypes/gazeboplugins/camera_push.cc > CMakeFiles/camera_push.dir/camera_push.cc.i

CMakeFiles/camera_push.dir/camera_push.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camera_push.dir/camera_push.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/samholmes/SEP-CTs/prototypes/gazeboplugins/camera_push.cc -o CMakeFiles/camera_push.dir/camera_push.cc.s

CMakeFiles/camera_push.dir/camera_push.cc.o.requires:
.PHONY : CMakeFiles/camera_push.dir/camera_push.cc.o.requires

CMakeFiles/camera_push.dir/camera_push.cc.o.provides: CMakeFiles/camera_push.dir/camera_push.cc.o.requires
	$(MAKE) -f CMakeFiles/camera_push.dir/build.make CMakeFiles/camera_push.dir/camera_push.cc.o.provides.build
.PHONY : CMakeFiles/camera_push.dir/camera_push.cc.o.provides

CMakeFiles/camera_push.dir/camera_push.cc.o.provides.build: CMakeFiles/camera_push.dir/camera_push.cc.o

# Object files for target camera_push
camera_push_OBJECTS = \
"CMakeFiles/camera_push.dir/camera_push.cc.o"

# External object files for target camera_push
camera_push_EXTERNAL_OBJECTS =

libcamera_push.so: CMakeFiles/camera_push.dir/camera_push.cc.o
libcamera_push.so: /usr/lib/libboost_system-mt.so
libcamera_push.so: CMakeFiles/camera_push.dir/build.make
libcamera_push.so: CMakeFiles/camera_push.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libcamera_push.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camera_push.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camera_push.dir/build: libcamera_push.so
.PHONY : CMakeFiles/camera_push.dir/build

CMakeFiles/camera_push.dir/requires: CMakeFiles/camera_push.dir/camera_push.cc.o.requires
.PHONY : CMakeFiles/camera_push.dir/requires

CMakeFiles/camera_push.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camera_push.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camera_push.dir/clean

CMakeFiles/camera_push.dir/depend:
	cd /home/samholmes/SEP-CTs/prototypes/gazeboplugins/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/samholmes/SEP-CTs/prototypes/gazeboplugins /home/samholmes/SEP-CTs/prototypes/gazeboplugins /home/samholmes/SEP-CTs/prototypes/gazeboplugins/build /home/samholmes/SEP-CTs/prototypes/gazeboplugins/build /home/samholmes/SEP-CTs/prototypes/gazeboplugins/build/CMakeFiles/camera_push.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/camera_push.dir/depend
