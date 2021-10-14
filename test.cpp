#include <gtest/gtest.h>

extern "C"
{
#include "server.h"
}

TEST(SERVER_TEST, Validate_dn_spec_sym)
{
  EXPECT_FALSE(ValidateDomainName("n@me"));
}

// TEST(SERVER_TEST, Compare_subnet)
// {
//   Server *servers;
//   Server test_server1 = {"abc", {172, 16, 17, 30}, {255, 255, 240, 0}, 1, 1};
//   servers[0] = test_server1;
//   //Server test_server1 = {"", {0,0,0,0}, {0,0,0,0}, 0, 0};
//   FourBytes subnet1 = {172, 16, 16, 0};
//   FourBytes subnets[1];
//   DefineSubnets(servers, subnets, 1);
//   EXPECT_EQ(subnets[0].b1, subnet1.b1);
// }

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}