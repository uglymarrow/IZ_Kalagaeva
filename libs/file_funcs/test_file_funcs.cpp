//
// Created by ksenia on 08.11.2021.
//

#include "gtest/gtest.h"
#include <cstring>
#include <cstdlib>

extern "C"{
#include "file_funcs.h"
#include "file_funcs.c"
}

TEST(FILE_TEST, check_open){
  EXPECT_EXIT(open_file("some.txt"), ::testing::ExitedWithCode(EXIT_FAILURE),"Can't open file");
}

TEST(ARRAY_TEST, check_close){
  EXPECT_EXIT(close_file(NULL), ::testing::ExitedWithCode(EXIT_FAILURE),"File doesn't exist");
}

int main(int argc, char**argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();

}