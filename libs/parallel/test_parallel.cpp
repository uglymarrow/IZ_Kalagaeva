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

int main(int argc, char**argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();

}