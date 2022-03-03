#include <gtest/gtest.h>
#include "binomial.h"


// ============= Zubair stencil Tests ================
TEST(BinomialTest, stencilBinomialTraversalTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    15, 365*15, 100, 100, 0, 0.25);

  // should be approx 37.7015
  EXPECT_GE(result, 37.70145);
  EXPECT_LT(result, 37.70155);
}

TEST(BinomialTest, stencilTriangleTest)
{
  // test case with number of blocks = 1 such that only tests on triangle
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    3, 365*3, 100, 100, 0, 0.25);

  // should be approx 18.5568
  EXPECT_GE(result, 18.55675);
  EXPECT_LT(result, 18.55685);
}

TEST(BinomialTest, stencilTwoBlockTest)
{
  // test case with number of blocks = 2 such that only tests on one rhombus and two triangles
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    7, 365*7, 100, 100, 0, 0.25);

  // should be approx 26.7855
  EXPECT_GE(result, 26.78545);
  EXPECT_LT(result, 26.78555);
}

TEST(BinomialTest, stencilDoesntDivideEvenly)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    9, 365*9, 100, 100, 0, 0.25);

  // should be approx 29.9802
  EXPECT_GE(result, 29.98015);
  EXPECT_LT(result, 29.98025);
}

TEST(BinomialTest, stencilOneOverDividingEvenly)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    8, 365*8, 100, 100, 0, 0.25);

  // should be approx 26.7855
  EXPECT_GE(result, 26.78545);
  EXPECT_LT(result, 26.78555);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}