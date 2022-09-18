#####################################################################
#                              PROJECT                              #
#####################################################################

# Set CMake Minimal Version
cmake_minimum_required(VERSION 3.3)

# Set Project Name
project(clustering VERSION 0.5)

# Set CPP Minimal Version
set(CMAKE_CXX_STANDARD 17)


#####################################################################
#                               DEPS                                #
#####################################################################

# Install GoogleTest from Sources
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Test if Gnuplot has been install on the computer
# and if true install Sciplot
include(FindGnuplot)
if (GNUPLOT_FOUND)
  message("GNUPLOT has been found, installing SCIPLOT")
  include_directories(deps/sciplot-master)

else()
  message("GNUPLOT was not found")
endif()


#####################################################################
#                            BUILD TYPE                             #
#####################################################################

# On choisit un type de compilation par défaut
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE RELEASE)
endif()

if(NOT USE_SCIPLOT)
        set(USE_SCIPLOT FALSE)
endif()

# On indique les options de compilation générales
set(CMAKE_CXX_FLAGS "-std=c++17")

# On indique les options de compilations pour des compilations spécifiques
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DBG "-O0 -g -Wall -Wextra --coverage") 


# On affiche un message à l'appel de cmake
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message("   Compiler CXX:         ${CMAKE_CXX_COMPILER}")
message("   Compiler CXX flags:         ${CMAKE_CXX_FLAGS}")

if(CMAKE_BUILD_TYPE MATCHES "DBG")
        message("   Compiler CXX debug flags:   ${CMAKE_CXX_FLAGS_DBG}")
endif(CMAKE_BUILD_TYPE MATCHES "DBG")

if(CMAKE_BUILD_TYPE MATCHES "RELEASE")
        message("   Compiler CXX release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif(CMAKE_BUILD_TYPE MATCHES "RELEASE")


#####################################################################
#                             Programm                              #
#####################################################################

# Path toward include directory
include_directories(includes)

# Find all source file and 
file(GLOB_RECURSE clustering_SOURCE_FILES src/*.cpp)

# Creation of libclustering.a
if (GNUPLOT_FOUND AND (CMAKE_BUILD_TYPE MATCHES "RELEASE" OR USE_SCIPLOT MATCHES TRUE))
  add_compile_definitions(__USE_SCIPLOT__)
  add_library(clustering ${clustering_SOURCE_FILES} ${sciplot_content_SOURCE_DIR})
else()
  add_library(clustering ${clustering_SOURCE_FILES})
endif()

add_executable(run src/main.cpp)

target_link_libraries(
  run
  clustering  
)

#####################################################################
#                               Tests                               #
#####################################################################

enable_testing()


# generate testing and coverage files
include(CTest)
include(Dart)

set(CTEST_BINARY_DIRECTORY "./bin")
# set gcov coverage options
set(
  CTEST_COVERAGE_COMMAND "/usr/bin/gcov"  
  CTEST_COVERAGE_EXTRA_FLAGS "--all-blocks --function-summaries --long-file-names --demangled-names"
  #CTEST_CUSTOM_COVERAGE_EXCLUDE "/home/gracques/Projets/Clustering/.build/_deps/*" "/usr/include/c++/"
)

# adding tests
add_executable(
  test_clustering
  tests/tests.cc
)

# linking GTest libraries
target_link_libraries(
  test_clustering
  gtest_main
)

# automates ctest test generation (add_test, ...)
include(GoogleTest)
gtest_discover_tests(test_clustering)
