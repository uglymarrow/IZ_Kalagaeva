//
// Created by ksenia on 08.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

extern "C"{
#include "array_funcs.h"
#include "array_funcs.c"
}

TEST(ARRAY_TEST, check_getfloat){
  EXPECT_EXIT(get_int(NULL), ::testing::ExitedWithCode(EXIT_FAILURE),"File doesn't exist");
}

TEST(ARRAY_TEST, check_create_array){
  EXPECT_EXIT(create_array(NULL, 0), ::testing::ExitedWithCode(EXIT_FAILURE),"File doesn't exist");
}


int main(int argc, char**argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();

}