#include <gtest/gtest.h>
#include "binomial.h"


// ============= Zubair stencil Tests ================
TEST(BinomialTest, stencilBinomialTraversalTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    15, 365*15, 100, 100, 0, 0.25);

  // should be approx 37.7079
  EXPECT_GE(result, 37.7078);
  EXPECT_LT(result, 37.7080);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}