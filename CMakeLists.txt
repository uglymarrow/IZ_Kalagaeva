CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(IZ2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Werror -Wpedantic")

add_library(FILE_FUNCS STATIC libs/file_funcs/file_funcs.c)
add_library(ARRAY_FUNCS STATIC libs/array_funcs/array_funcs.c )
add_library(SEARCH_CONSISTENT STATIC libs/consistent/search.c)
add_library(SEARCH_PARALLEL SHARED libs/parallel/search.c )

add_executable(IZ2 main.c)
target_link_libraries(IZ2 ${CMAKE_DL_LIBS} FILE_FUNCS)
target_link_libraries(IZ2 ${CMAKE_DL_LIBS} ARRAY_FUNCS)
if (CMAKE_PARALLEL)
    message("PARALLEL")
    target_link_libraries(IZ2 ${CMAKE_DL_LIBS} SEARCH_PARALLEL)
else()
    target_link_libraries(IZ2 ${CMAKE_DL_LIBS} SEARCH_CONSISTENT)
endif()

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
message(${GTEST_LIBRARIES})

add_executable(tests_consistent libs/consistent/test_consistent.cpp )
add_executable(tests_parallel libs/parallel/test_parallel.cpp )
add_executable(tests_file_funcs libs/file_funcs/test_file_funcs.cpp )
add_executable(tests_array_funcs libs/array_funcs/tests_array_funcs.cpp)


target_link_libraries(tests_consistent ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_consistent  SEARCH_CONSISTENT)
target_link_libraries(tests_consistent FILE_FUNCS)

target_link_libraries(tests_parallel ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_parallel SEARCH_PARALLEL)
target_link_libraries(tests_parallel FILE_FUNCS)

target_link_libraries(tests_file_funcs ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_file_funcs FILE_FUNCS)

target_link_libraries(tests_array_funcs ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_array_funcs ARRAY_FUNCS)