######################################################################
# Set the minimum CMake version.
######################################################################
if(WIN32)
  cmake_minimum_required(VERSION 3.1)
else()
  cmake_minimum_required(VERSION 2.8.9)
endif()

##################################################################################
# Set some CMake Policies.
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
##################################################################################
set(project_policies
  CMP0001 # NEW: CMAKE_BACKWARDS_COMPATIBILITY should no longer be used.
  CMP0002 # NEW: Logical target names must be globally unique.
  CMP0003 # NEW: Libraries linked via full path no longer produce linker search paths.
  CMP0004 # NEW: Libraries linked may NOT have leading or trailing whitespace.
  CMP0005 # NEW: Preprocessor definition values are now escaped automatically.
  CMP0006 # NEW: Installing MACOSX_BUNDLE targets requires a BUNDLE DESTINATION.
  CMP0007 # NEW: List command no longer ignores empty elements.
  CMP0008 # NEW: Libraries linked by full-path must have a valid library file name.
  CMP0009 # NEW: FILE GLOB_RECURSE calls should not follow symlinks by default.
  CMP0010 # NEW: Bad variable reference syntax is an error.
  CMP0011 # NEW: Included scripts do automatic cmake_policy PUSH and POP.
  CMP0012 # NEW: if() recognizes numbers and boolean constants.
  CMP0013 # NEW: Duplicate binary directories are not allowed.
  CMP0014 # NEW: Input directories must have CMakeLists.txt
  )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

if (NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
  # CMP0048 # OLD: Leave VERSION variables untouched.
  cmake_policy(SET CMP0048 OLD)
endif ()

if (NOT ${CMAKE_VERSION} VERSION_LESS "3.1")
  # CMP0053 # OLD: Leave references and variable expansion as pre version 3.1.
  cmake_policy(SET CMP0053 OLD)
endif ()

######################################################################
# Find Boost
######################################################################
find_package(Boost 1.45.0 COMPONENTS filesystem program_options) 
include_directories(${Boost_INCLUDE_DIRS}) 


######################################################################
# Add C++11 and OpenMP support
######################################################################

# Set compiler to gcc for OSX -- necessary for OpenMP.
# Make sure to link against Boost compiled with gcc, not clang.
if(APPLE)
  SET(CMAKE_C_COMPILER g++-5)
  SET(CMAKE_CXX_COMPILER g++-5)
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fopenmp -O3")

######################################################################
# Setup the path to load CMake macros, and extra CMake files.
######################################################################
set(CMAKE_MODULE_PATH
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake
    #${CMAKE_SOURCE_DIR}/CMake/CMakeExternals
    ${CMAKE_MODULE_PATH}
   )

######################################################################
# Now set up flags for this project.
######################################################################
option(BUILD_SHARED_LIBS "Build GAME_OF_LIFE with shared libraries." OFF)
mark_as_advanced(BUILD_SHARED_LIBS)

######################################################################
# End of SuperBuild. Print out where the source and binary folders
# are, just to make it really explicit... well, explicit to the user
# that bothers to read these messages! :-)
######################################################################
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

######################################################################
# Setup further include folders
######################################################################
include_directories(inc)
 
######################################################################
# Decide what subdirectories we are building, and go and build them.
######################################################################
add_subdirectory(src bin)
add_subdirectory(test)
