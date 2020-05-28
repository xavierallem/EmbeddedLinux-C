# Set the CMake minimum version
cmake_minimum_required(VERSION 3.5)

# Declare the Project version and the Language that the project is written in
project(module2 VERSION 1.0.0 LANGUAGES C CXX)

# Set the Build Type to Release
# Ideally there should be more Build Types, but for now there is only one
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -D_GNU_SOURCE ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wformat=2 -Wall -Wextra -Winline -pipe")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

include_directories("include/")

add_definitions(-D__STDC_FORMAT_MACROS)
set_property(DIRECTORY PROPERTY COMPILE_OPTIONS ${EXTRA_CXX_FLAGS})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Add rules to create the binary files
add_executable(problem1 problem1.c)
add_executable(problem2 problem2.c)
add_executable(problem3 problem3.c)

target_link_libraries(problem1 PUBLIC  -lm )
target_link_libraries(problem2 PUBLIC  -lm )
target_link_libraries(problem3 PUBLIC  -lm )


