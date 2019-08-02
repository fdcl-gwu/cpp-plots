cmake_minimum_required (VERSION 3.1)
project(CPP-PLOT)

set (CMAKE_CXX_STANDARD 11)

link_directories("/usr/local/lib/")
include_directories("/usr/local/include/")
include_directories("/usr/include/python2.7")
include_directories("/usr/local/lib/python2.7/dist-packages/numpy/core/include/")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libraries/matplotlib-cpp)

find_package (PkgConfig REQUIRED)
find_package(PythonLibs 2.7)

set(plot_src
src/main.cpp
)
add_executable(plot ${plot_src})
target_compile_options(plot
    PUBLIC -Wall -o -std=c++11
)
target_include_directories(plot PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(plot ${PYTHON_LIBRARIES})
    