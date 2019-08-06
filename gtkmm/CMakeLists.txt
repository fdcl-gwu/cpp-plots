cmake_minimum_required (VERSION 3.1)
project(CPP-PLOT-GTKMM)

set (CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)

pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

pkg_check_modules(GTKMMPLPLOT gtkmm-plplot-2.0)

link_directories("/usr/local/lib/")
include_directories("/usr/local/include/")

# Hello World ##################################################################
set(hello_world_src
    src/main_hello_world.cpp
)
add_executable(hello_world ${hello_world_src})
target_compile_options(hello_world
    PUBLIC -Wall -o -std=c++11
)
target_include_directories(hello_world
PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
)
target_link_libraries(hello_world 
    ${GTKMM_LIBRARIES}
)

# GTKMM-PLPLOT example #########################################################
set(plot_hello_world_src
    src/main_plplot.cpp
)
add_executable(hello_world_plot ${plot_hello_world_src})
target_compile_options(hello_world_plot
    PUBLIC -Wall -o -std=c++11
)
target_include_directories(hello_world_plot
PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${GTKMMPLPLOT_INCLUDE_DIRS}
)
target_link_libraries(hello_world_plot 
    ${GTKMM_LIBRARIES}
    ${GTKMMPLPLOT_LIBRARIES}
)

# Minimal Working Example ######################################################
set(mwe_src
    src/main_mwe.cpp
)
add_executable(minimal_working_example ${mwe_src})
target_compile_options(minimal_working_example
    PUBLIC -Wall -o -std=c++11
)
target_include_directories(minimal_working_example
PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${GTKMMPLPLOT_INCLUDE_DIRS}
)
target_link_libraries(minimal_working_example 
    ${GTKMM_LIBRARIES}
    ${GTKMMPLPLOT_LIBRARIES}
)