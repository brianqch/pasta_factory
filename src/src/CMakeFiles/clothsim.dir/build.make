# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/emilyxiao/Desktop/pasta_factory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/emilyxiao/Desktop/pasta_factory/src

# Include any dependencies generated for this target.
include src/CMakeFiles/clothsim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/clothsim.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/clothsim.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/clothsim.dir/flags.make

src/CMakeFiles/clothsim.dir/cloth.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/cloth.cpp.o: cloth.cpp
src/CMakeFiles/clothsim.dir/cloth.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/clothsim.dir/cloth.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/cloth.cpp.o -MF CMakeFiles/clothsim.dir/cloth.cpp.o.d -o CMakeFiles/clothsim.dir/cloth.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/cloth.cpp

src/CMakeFiles/clothsim.dir/cloth.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/cloth.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/cloth.cpp > CMakeFiles/clothsim.dir/cloth.cpp.i

src/CMakeFiles/clothsim.dir/cloth.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/cloth.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/cloth.cpp -o CMakeFiles/clothsim.dir/cloth.cpp.s

src/CMakeFiles/clothsim.dir/clothMesh.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/clothMesh.cpp.o: clothMesh.cpp
src/CMakeFiles/clothsim.dir/clothMesh.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/clothsim.dir/clothMesh.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/clothMesh.cpp.o -MF CMakeFiles/clothsim.dir/clothMesh.cpp.o.d -o CMakeFiles/clothsim.dir/clothMesh.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/clothMesh.cpp

src/CMakeFiles/clothsim.dir/clothMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/clothMesh.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/clothMesh.cpp > CMakeFiles/clothsim.dir/clothMesh.cpp.i

src/CMakeFiles/clothsim.dir/clothMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/clothMesh.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/clothMesh.cpp -o CMakeFiles/clothsim.dir/clothMesh.cpp.s

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: collision/sphere.cpp
src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o -MF CMakeFiles/clothsim.dir/collision/sphere.cpp.o.d -o CMakeFiles/clothsim.dir/collision/sphere.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/collision/sphere.cpp

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/sphere.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/collision/sphere.cpp > CMakeFiles/clothsim.dir/collision/sphere.cpp.i

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/sphere.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/collision/sphere.cpp -o CMakeFiles/clothsim.dir/collision/sphere.cpp.s

src/CMakeFiles/clothsim.dir/collision/plane.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/plane.cpp.o: collision/plane.cpp
src/CMakeFiles/clothsim.dir/collision/plane.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/clothsim.dir/collision/plane.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/collision/plane.cpp.o -MF CMakeFiles/clothsim.dir/collision/plane.cpp.o.d -o CMakeFiles/clothsim.dir/collision/plane.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/collision/plane.cpp

src/CMakeFiles/clothsim.dir/collision/plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/plane.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/collision/plane.cpp > CMakeFiles/clothsim.dir/collision/plane.cpp.i

src/CMakeFiles/clothsim.dir/collision/plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/plane.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/collision/plane.cpp -o CMakeFiles/clothsim.dir/collision/plane.cpp.s

src/CMakeFiles/clothsim.dir/collision/belt.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/belt.cpp.o: collision/belt.cpp
src/CMakeFiles/clothsim.dir/collision/belt.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/clothsim.dir/collision/belt.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/collision/belt.cpp.o -MF CMakeFiles/clothsim.dir/collision/belt.cpp.o.d -o CMakeFiles/clothsim.dir/collision/belt.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/collision/belt.cpp

src/CMakeFiles/clothsim.dir/collision/belt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/belt.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/collision/belt.cpp > CMakeFiles/clothsim.dir/collision/belt.cpp.i

src/CMakeFiles/clothsim.dir/collision/belt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/belt.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/collision/belt.cpp -o CMakeFiles/clothsim.dir/collision/belt.cpp.s

src/CMakeFiles/clothsim.dir/collision/splitter.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/splitter.cpp.o: collision/splitter.cpp
src/CMakeFiles/clothsim.dir/collision/splitter.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/clothsim.dir/collision/splitter.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/collision/splitter.cpp.o -MF CMakeFiles/clothsim.dir/collision/splitter.cpp.o.d -o CMakeFiles/clothsim.dir/collision/splitter.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/collision/splitter.cpp

src/CMakeFiles/clothsim.dir/collision/splitter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/splitter.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/collision/splitter.cpp > CMakeFiles/clothsim.dir/collision/splitter.cpp.i

src/CMakeFiles/clothsim.dir/collision/splitter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/splitter.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/collision/splitter.cpp -o CMakeFiles/clothsim.dir/collision/splitter.cpp.s

src/CMakeFiles/clothsim.dir/collision/box.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/box.cpp.o: collision/box.cpp
src/CMakeFiles/clothsim.dir/collision/box.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/clothsim.dir/collision/box.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/collision/box.cpp.o -MF CMakeFiles/clothsim.dir/collision/box.cpp.o.d -o CMakeFiles/clothsim.dir/collision/box.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/collision/box.cpp

src/CMakeFiles/clothsim.dir/collision/box.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/box.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/collision/box.cpp > CMakeFiles/clothsim.dir/collision/box.cpp.i

src/CMakeFiles/clothsim.dir/collision/box.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/box.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/collision/box.cpp -o CMakeFiles/clothsim.dir/collision/box.cpp.s

src/CMakeFiles/clothsim.dir/main.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/main.cpp.o: main.cpp
src/CMakeFiles/clothsim.dir/main.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/clothsim.dir/main.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/main.cpp.o -MF CMakeFiles/clothsim.dir/main.cpp.o.d -o CMakeFiles/clothsim.dir/main.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/main.cpp

src/CMakeFiles/clothsim.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/main.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/main.cpp > CMakeFiles/clothsim.dir/main.cpp.i

src/CMakeFiles/clothsim.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/main.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/main.cpp -o CMakeFiles/clothsim.dir/main.cpp.s

src/CMakeFiles/clothsim.dir/clothSimulator.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/clothSimulator.cpp.o: clothSimulator.cpp
src/CMakeFiles/clothsim.dir/clothSimulator.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/clothsim.dir/clothSimulator.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/clothSimulator.cpp.o -MF CMakeFiles/clothsim.dir/clothSimulator.cpp.o.d -o CMakeFiles/clothsim.dir/clothSimulator.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/clothSimulator.cpp

src/CMakeFiles/clothsim.dir/clothSimulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/clothSimulator.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/clothSimulator.cpp > CMakeFiles/clothsim.dir/clothSimulator.cpp.i

src/CMakeFiles/clothsim.dir/clothSimulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/clothSimulator.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/clothSimulator.cpp -o CMakeFiles/clothsim.dir/clothSimulator.cpp.s

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: misc/sphere_drawing.cpp
src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o -MF CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.d -o CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/misc/sphere_drawing.cpp

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/misc/sphere_drawing.cpp > CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/misc/sphere_drawing.cpp -o CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s

src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.o: misc/file_utils.cpp
src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.o -MF CMakeFiles/clothsim.dir/misc/file_utils.cpp.o.d -o CMakeFiles/clothsim.dir/misc/file_utils.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/misc/file_utils.cpp

src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/misc/file_utils.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/misc/file_utils.cpp > CMakeFiles/clothsim.dir/misc/file_utils.cpp.i

src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/misc/file_utils.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/misc/file_utils.cpp -o CMakeFiles/clothsim.dir/misc/file_utils.cpp.s

src/CMakeFiles/clothsim.dir/camera.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/camera.cpp.o: camera.cpp
src/CMakeFiles/clothsim.dir/camera.cpp.o: src/CMakeFiles/clothsim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/clothsim.dir/camera.cpp.o"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/clothsim.dir/camera.cpp.o -MF CMakeFiles/clothsim.dir/camera.cpp.o.d -o CMakeFiles/clothsim.dir/camera.cpp.o -c /Users/emilyxiao/Desktop/pasta_factory/src/camera.cpp

src/CMakeFiles/clothsim.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/camera.cpp.i"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emilyxiao/Desktop/pasta_factory/src/camera.cpp > CMakeFiles/clothsim.dir/camera.cpp.i

src/CMakeFiles/clothsim.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/camera.cpp.s"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emilyxiao/Desktop/pasta_factory/src/camera.cpp -o CMakeFiles/clothsim.dir/camera.cpp.s

# Object files for target clothsim
clothsim_OBJECTS = \
"CMakeFiles/clothsim.dir/cloth.cpp.o" \
"CMakeFiles/clothsim.dir/clothMesh.cpp.o" \
"CMakeFiles/clothsim.dir/collision/sphere.cpp.o" \
"CMakeFiles/clothsim.dir/collision/plane.cpp.o" \
"CMakeFiles/clothsim.dir/collision/belt.cpp.o" \
"CMakeFiles/clothsim.dir/collision/splitter.cpp.o" \
"CMakeFiles/clothsim.dir/collision/box.cpp.o" \
"CMakeFiles/clothsim.dir/main.cpp.o" \
"CMakeFiles/clothsim.dir/clothSimulator.cpp.o" \
"CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o" \
"CMakeFiles/clothsim.dir/misc/file_utils.cpp.o" \
"CMakeFiles/clothsim.dir/camera.cpp.o"

# External object files for target clothsim
clothsim_EXTERNAL_OBJECTS =

clothsim: src/CMakeFiles/clothsim.dir/cloth.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/clothMesh.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/plane.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/belt.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/splitter.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/box.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/main.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/clothSimulator.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/misc/file_utils.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/camera.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/build.make
clothsim: CGL/src/libCGL.a
clothsim: ext/nanogui/libnanogui.dylib
clothsim: /usr/local/lib/libfreetype.dylib
clothsim: src/CMakeFiles/clothsim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/emilyxiao/Desktop/pasta_factory/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable ../clothsim"
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clothsim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/clothsim.dir/build: clothsim
.PHONY : src/CMakeFiles/clothsim.dir/build

src/CMakeFiles/clothsim.dir/clean:
	cd /Users/emilyxiao/Desktop/pasta_factory/src/src && $(CMAKE_COMMAND) -P CMakeFiles/clothsim.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/clothsim.dir/clean

src/CMakeFiles/clothsim.dir/depend:
	cd /Users/emilyxiao/Desktop/pasta_factory/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emilyxiao/Desktop/pasta_factory /Users/emilyxiao/Desktop/pasta_factory/src /Users/emilyxiao/Desktop/pasta_factory/src /Users/emilyxiao/Desktop/pasta_factory/src/src /Users/emilyxiao/Desktop/pasta_factory/src/src/CMakeFiles/clothsim.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/clothsim.dir/depend

