#include <gtest/gtest.h>

extern "C"
{
#include "server.h"
}

TEST(SERVER_TEST, Validate_dn_spec_sym)
{
  EXPECT_FALSE(validate_domain_name("n@me"));
}

TEST(SERVER_TEST, Test_subnetting)
{
  server *servers = NULL;
  servers = (server *)realloc(servers, sizeof(server));
  server test_server1 = {"abc", {172, 16, 17, 30}, {255, 255, 240, 0}, 1, 1};
  servers[0] = test_server1;
  // server test_server1 = {"", {0,0,0,0}, {0,0,0,0}, 0, 0};
  four_bytes subnet1 = {172, 16, 16, 0};
  four_bytes subnets[1];
  define_subnets(servers, subnets, 1);
  EXPECT_EQ(subnets[0].b1, subnet1.b1);
  EXPECT_EQ(subnets[0].b2, subnet1.b2);
  EXPECT_EQ(subnets[0].b3, subnet1.b3);
  EXPECT_EQ(subnets[0].b4, subnet1.b4);
}

TEST(SERVER_TEST, Validate_dn_def_sym)
{
  EXPECT_EXIT(validate_domain_name("-namem-"), ::testing::ExitedWithCode(1), "Domain name contains '-' symbol at wrong position \n");
}

TEST(SERVER_TEST, Validate_dn_short)
{
  EXPECT_EXIT(validate_domain_name("n"), ::testing::ExitedWithCode(1), "Domain name length is too short \n");
}

TEST(SERVER_TEST, Validate_dn_long)
{
  char long_name[500] = {'\0'};
  EXPECT_FALSE(validate_domain_name(long_name));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}