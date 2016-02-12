cmake_minimum_required(VERSION 2.6)
project(andres-partition-comparison)
include_directories(include include/andres)
file(GLOB headers include/andres/*.hxx)
enable_testing()

##############################################################################
# C++11 support
##############################################################################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Some functionality will not be available.")
endif()

find_package(Matlab QUIET)
if(MATLAB_FOUND)
    INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR})
    message(STATUS "MATLAB found")
else()
    message("MATLAB not found")
endif()

add_executable(test-partition-comparison src/unittest/partition-comparison.cxx ${headers})
add_test(test-partition-comparison test-partition-comparison)

if(MATLAB_FOUND)
   add_library(andres_rand_index SHARED src/mex/andres_rand_index.cxx src/mex/andres_rand_index.def ${headers})
   target_link_libraries(andres_rand_index ${MATLAB_LIBRARIES})

   add_library(andres_variation_of_information SHARED src/mex/andres_variation_of_information.cxx src/mex/andres_variation_of_information.def ${headers})
   target_link_libraries(andres_variation_of_information ${MATLAB_LIBRARIES})
endif()

