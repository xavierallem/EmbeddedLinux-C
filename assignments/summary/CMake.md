# CMake Summary

## Introduction

![Cmake](assignments/summary/Assets/as.png)

**CMake** is an extensible, open-source system that manages the build process in an operating system and in a compiler-independent manner.CMake can generate a native build environment that will compile source code, create libraries, generate wrappers and build executable binaries in arbitrary combinations. CMake supports in-place and out-of-place builds, 
and can therefore support multiple builds from a single source tree.

## Keypoints 

Build logic and definitions with CMake language is written either in CMakeLists.txt.

![Cmake](assignments/summary/Assets/H2vmf.png)

- *CMakeLists.txt* file is placed at the source of the project you want to build.
- *CMakeLists.txt* is placed at the root of the source tree of any application, library it will work for.
- If there are multiple modules, and each module can be compiled and built separately, *CMakeLists.txt* can be inserted into the sub folder.
- *.cmake* files can be used as scripts, which runs cmake command to prepare environment pre-processing or split tasks which can be written outside of *CMakeLists.txt*.
- *.cmake* files can also define modules for projects. These projects can be separated build processes for libraries or extra methods for complex, multi-module projects.

## CMake Commands

### Commonly used Commands

- _**message**_ : prints given message
- _**cmake_minimum_required**_ : sets minimum version of cmake to be used
- _**add_executable**_ : adds executable target with given name
- _**add_library**_ : adds a library target to be build from listed source files
- _**add_subdirectory**_ : adds a subdirectory to build

### Conditional commands

There are also commands to enable developers write out conditional statements, loops, iterate on list, assignments:

- _**if, endif**_
- _**elif, endif**_
- _**while, endwhile**_
- _**foreach, endforeach**_
- _**list**_
- _**return**_
- _**set_property**_(assign value to variable.)

All conditional statements should be ended with its corresponding end command (endif, endwhile, endforeach etc).

## CMake Variables

CMake includes predefined variables which are set by default as location of source tree and system components.

- _**CMAKE_BINARY_DIR**_ : Full path to top level of build tree and binary output folder, by default it is defined as top level of build tree.
- _**CMAKE_HOME_DIRECTORY**_ : Path to top of source tree.
- _**CMAKE_SOURCE_DIR**_ : Full path to top level of source tree.
- _**CMAKE_INCLUDE_PATH**_ : Path used to find file, path.

Variable values can be accessed with ${variable_name}.
```
message("CXX Standard: ${CMAKE_CXX_STANDARD}")
```
To set a variable value
```
set(TRIAL_VARIABLE "VALUE")
message("${TRIAL_VARIABLE}")
```

## Building a C++ code with CMake

- First we write the c++ code
 ```c++
 #include <iostream>
int main() {
	std::cout<<"Hello CMake!"<<std::endl;
}
```

- Writing the CMake script
```
cmake_minimum_required(VERSION 3.9.1)
project(CMakeHello)
add_executable(cmake_hello main.cpp)
```
- Run the cmake command with the CMake script
```bash
$ cmake CMakeLists.txt

```
- Build the project 
```bash
$ make all
```



