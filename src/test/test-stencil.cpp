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

TEST(BinomialTest, stencilAmericanCallTriangleTest)
{
  // test case with number of blocks = 1 such that only tests on triangle
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanCall>(
    3, 365*3, 100, 100, 0, 0.25);

  // should be approx 18.5568
  EXPECT_GE(result, 18.55675);
  EXPECT_LT(result, 18.55685);
}

TEST(BinomialTest, stencilAmericanPutTriangleTest)
{
  // test case with number of blocks = 1 such that only tests on triangle
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanPut>(
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

TEST(BinomialTest, stencilAmericanPutTwoBlockTest)
{
  // test case with number of blocks = 2 such that only tests on one rhombus and two triangles
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanPut>(
    7, 365*7, 100, 100, 0, 0.25);

  // should be approx 26.7855
  EXPECT_GE(result, 26.78545);
  EXPECT_LT(result, 26.78555);
}

TEST(BinomialTest, stencilAmericanCallTwoBlockTest)
{
  // test case with number of blocks = 2 such that only tests on one rhombus and two triangles
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanCall>(
    7, 365*7, 100, 100, 0, 0.25);

  // should be approx 26.7855
  EXPECT_GE(result, 26.78545);
  EXPECT_LT(result, 26.78555);
}

TEST(BinomialTest, stencilAmericanCallThreeBlockTest)
{
  // test case with number of blocks = 3 
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanCall>(
    11, 365*11, 100, 100, 0, 0.25);

  // should be approx 32.8111
  EXPECT_GE(result, 32.81105);
  EXPECT_LT(result, 32.81115);
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

TEST(BinomialTest, europeanCallQLTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, europeanCallQLNoDividendTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, europeanPutQLTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::QLEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4880
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.4881);
}

TEST(BinomialTest, americanCallQLTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::QLAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.8586
  EXPECT_GE(result, 6.85855);
  EXPECT_LT(result, 6.85865);
}

TEST(BinomialTest, americanCallQLNoDividendTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::QLAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, americanPutQLTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::QLAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4881
  EXPECT_GE(result, 10.48805);
  EXPECT_LT(result, 10.48815);
}

// =========== Zubair tests ==============
TEST(BinomialTest, europeanCallZubairTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, europeanCallZubairNoDividendTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, europeanPutZubairTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4880
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.4881);
}

TEST(BinomialTest, americanCallZubairTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.8586
  EXPECT_GE(result, 6.85855);
  EXPECT_LT(result, 6.85865);
}

TEST(BinomialTest, americanCallZubairNoDividendTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, americanPutZubairTest)
{
  double result = Binomial::stencilBinomialTraversal<Binomial::ZubairAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4881
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.48815);
}

// ==============Parallel Stencil Test=====================

TEST(BinomialTest, parTriangleTest)
{
  // test case with number of blocks = 1 such that only tests on triangle
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    3, 365*3, 100, 100, 0, 0.25);

  // should be approx 18.5568
  EXPECT_GE(result, 18.55675);
  EXPECT_LT(result, 18.55685);
}

// Test with just 2 blocks
TEST(BinomialTest, parTwoBlockTest)
{
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    7, 7*365, 100, 100, 0, 0.25);

  // should be approx 26.7855
  EXPECT_GE(result, 26.78545);
  EXPECT_LT(result, 26.78555);
}

TEST(BinomialTest, parThreeBlockTest)
{
  // test case with number of blocks = 3 
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    11, 365*11, 100, 100, 0, 0.25);

  // should be approx 32.8111
  EXPECT_GE(result, 32.81105);
  EXPECT_LT(result, 32.81115);
}

TEST(BinomialTest, parOneTriangleOneEdgeBlock)
{
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    4, 365*4, 100, 100, 0, 0.25);

  // should be approx 18.5568
  EXPECT_GE(result, 18.55675);
  EXPECT_LT(result, 18.55685);
}

TEST(BinomialTest, parOneTriangleOneEdgeBlockSize2)
{
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    5, 365*5, 100, 100, 0, 0.25);

  // should be approx 23.0769
  EXPECT_GE(result, 23.07685);
  EXPECT_LT(result, 23.07695);
}

TEST(BinomialTest, parOneOverDividingEvenly)
{
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    8, 365*8, 100, 100, 0, 0.25);

  // should be approx 26.7855
  EXPECT_GE(result, 26.78545);
  EXPECT_LT(result, 26.78555);
}

TEST(BinomialTest, parDoesntDivideEvenly)
{
  double result = Binomial::parallelStencilBinomialTraversal<Binomial::ZubairEuropeanCall>(
    9, 365*9, 100, 100, 0, 0.25);

  // should be approx 29.9802
  EXPECT_GE(result, 29.98015);
  EXPECT_LT(result, 29.98025);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
