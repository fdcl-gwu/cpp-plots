cmake_minimum_required (VERSION 3.1)
project(CPP-PLOT-SERVER)

set (CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

link_directories("/usr/local/lib/")
include_directories("/usr/local/include/")
include_directories(${PROJECT_SOURCE_DIR}/include)

set(main_src
    src/main.cpp
    src/plotting_server.cpp
)
add_executable(server ${main_src})
target_compile_options(server
    PUBLIC -Wall -o -std=c++11 -pthread
)
target_link_libraries(server
    Threads::Threads
)