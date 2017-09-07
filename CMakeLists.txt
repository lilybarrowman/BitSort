cmake_minimum_required(VERSION 3.0.0)
project(BitSort)
set(CMAKE_BUILD_TYPE RELWITHDEBINFO)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")

add_executable(BitSort ${SOURCES})