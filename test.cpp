#include <gtest/gtest.h>

extern "C"
{
#include "server.h"
}

TEST(server_TEST, Validate_dn_spec_sym)
{
  EXPECT_FALSE(validate_domain_name("n@me"));
}

TEST(server_TEST, Test_subnetting)
{
  server *servers =  NULL;
  servers = (server *)realloc(servers, sizeof(server));
  server test_server1 = {"abc", {172, 16, 17, 30}, {255, 255, 240, 0}, 1, 1};
  servers[0] = test_server1;
  //server test_server1 = {"", {0,0,0,0}, {0,0,0,0}, 0, 0};
  four_bytes subnet1 = {172, 16, 16, 0};
  four_bytes subnets[1];
  define_subnets(servers, subnets, 1);
  EXPECT_EQ(subnets[0].b1, subnet1.b1);
  EXPECT_EQ(subnets[0].b2, subnet1.b2);
  EXPECT_EQ(subnets[0].b3, subnet1.b3);
  EXPECT_EQ(subnets[0].b4, subnet1.b4);
}

TEST(server_TEST, Validate_dn_def_sym)
{
  EXPECT_FALSE(validate_domain_name("-namem-"));
}

TEST(server_TEST, Validate_dn_short)
{
  EXPECT_FALSE(validate_domain_name("n"));
}

TEST(server_TEST, Validate_dn_long)
{
  char long_name[500] = {'\0'};
  EXPECT_FALSE(validate_domain_name(long_name));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}