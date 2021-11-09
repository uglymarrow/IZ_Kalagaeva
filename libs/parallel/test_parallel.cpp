#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

extern "C"{
#include "./search.h"
#include "./search.c"
}

TEST(PAR_SEARCH_TEST, check_par_search){
  EXPECT_EXIT(search(NULL, 0), ::testing::ExitedWithCode(EXIT_FAILURE),"Function parallel/search. Array doesn't exist");
}

int main(int argc, char**argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();

}