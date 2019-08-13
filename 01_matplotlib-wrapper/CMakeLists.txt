cmake_minimum_required (VERSION 3.1)
project(CPP-PLOT)

set (CMAKE_CXX_STANDARD 11)

link_directories("/usr/local/lib/")
include_directories("/usr/local/include/")
include_directories("/usr/include/python2.7")
include_directories("/usr/local/lib/python2.7/dist-packages/numpy/core/include/")

# Required for macOS
include_directories("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/matplotlib-cpp)

find_package (PkgConfig REQUIRED)
find_package(PythonLibs 2.7)
message("${PYTHON_INCLUDE_DIRS}")
message("${PYTHON_LIBRARIES}")

set(plot_line_src
    src/main_line.cpp
)
add_executable(plot_line ${plot_line_src})
target_compile_options(plot_line
    PUBLIC -Wall -o -std=c++11
)
target_include_directories(plot_line 
    PRIVATE 
    ${PYTHON_INCLUDE_DIRS}
)
target_link_libraries(plot_line ${PYTHON_LIBRARIES})
    

set(animate_src
    src/main_animate.cpp
)
add_executable(animate ${animate_src})
target_compile_options(plot_line
    PUBLIC -Wall -o -std=c++11
)
target_include_directories(animate PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(animate ${PYTHON_LIBRARIES})