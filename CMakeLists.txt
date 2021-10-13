cmake_minimum_required(VERSION 3.10)

project(subnetting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCE_FILES server_lib.c)
add_library(server_lib STATIC ${LIB_SOURCE_FILES})

add_executable(main main.c)
target_link_libraries(main server_lib)

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(testing test.cpp)
target_link_libraries(testing ${GTEST_LIBRARIES} pthread server_lib)
