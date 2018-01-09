#include "helper.h"
#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;
using namespace cool_helper;
TEST(CoolHelperTest, ToEscapedStringTest) {
  const std::string test1_in = "\\\"\n\t\b\f";
  const std::string test1_out = "\\\\\\\"\\n\\t\\b\\f";

  EXPECT_TRUE(test1_out == ToEscapedString(test1_in));
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

