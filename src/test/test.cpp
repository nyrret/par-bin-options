#include <gtest/gtest.h>
#include "binomial.h"

TEST(BinomialTest, europeanCallTest)
{
  // double result = Binomial::europeanCall(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // EXPECT_LE(europeanCall(100, 252, 127.62, 130, 0.001, 0.20, 0.0163), 6.76954);
  // EXPECT_GE(europeanCall(100, 252, 127.62, 130, 0.001, 0.20, 0.0163), 6.76950);
}

TEST(BinomialTest, zubairBinomialTest)
{
  EXPECT_LE(32, 6.76954);
  EXPECT_GE(32, 6.76950);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}