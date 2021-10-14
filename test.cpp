#include <gtest/gtest.h>

extern "C"
{
#include "server.h"
}

TEST(SERVER_TEST, Validate_dn_spec_sym)
{
  EXPECT_FALSE(ValidateDomainName("n@me"));
}

TEST(SERVER_TEST, Test_subnetting)
{
  Server *servers =  NULL;
  servers = (Server *)realloc(servers, sizeof(Server));
  Server test_server1 = {"abc", {172, 16, 17, 30}, {255, 255, 240, 0}, 1, 1};
  servers[0] = test_server1;
  //Server test_server1 = {"", {0,0,0,0}, {0,0,0,0}, 0, 0};
  FourBytes subnet1 = {172, 16, 16, 0};
  FourBytes subnets[1];
  DefineSubnets(servers, subnets, 1);
  EXPECT_EQ(subnets[0].b1, subnet1.b1);
  EXPECT_EQ(subnets[0].b2, subnet1.b2);
  EXPECT_EQ(subnets[0].b3, subnet1.b3);
  EXPECT_EQ(subnets[0].b4, subnet1.b4);
}

TEST(SERVER_TEST, Validate_dn_def_sym)
{
  EXPECT_FALSE(ValidateDomainName("-namem-"));
}

TEST(SERVER_TEST, Validate_dn_short)
{
  EXPECT_FALSE(ValidateDomainName("n"));
}

TEST(SERVER_TEST, Validate_dn_long)
{
  char long_name[500] = {'\0'};
  EXPECT_FALSE(ValidateDomainName(long_name));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}