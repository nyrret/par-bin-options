#include <gtest/gtest.h>
#include "binomial.h"
#include "original-binomial.h"


// ============= Original tests ================
TEST(BinomialTest, originalEuropeanCallQLTest)
{
  double result = Binomial::qlEuropeanCall(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, originalEuropeanCallZubairTest)
{
  double result = Binomial::zubairEuropeanCall(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

// ============= QuantLib tests ================
TEST(BinomialTest, europeanCallQLTest)
{
  double result = Binomial::binomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, europeanCallQLNoDividendTest)
{
  double result = Binomial::binomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, europeanPutQLTest)
{
  double result = Binomial::binomialTraversal<Binomial::QLEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4880
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.4881);
}

TEST(BinomialTest, americanCallQLTest)
{
  double result = Binomial::binomialTraversal<Binomial::QLAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.8586
  EXPECT_GE(result, 6.85855);
  EXPECT_LT(result, 6.85865);
}

TEST(BinomialTest, americanCallQLNoDividendTest)
{
  double result = Binomial::binomialTraversal<Binomial::QLAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, americanPutQLTest)
{
  double result = Binomial::binomialTraversal<Binomial::QLAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4881
  EXPECT_GE(result, 10.48805);
  EXPECT_LT(result, 10.48815);
}

// =========== Zubair tests ==============
TEST(BinomialTest, europeanCallZubairTest)
{
  double result = Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, europeanCallZubairNoDividendTest)
{
  double result = Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, europeanPutZubairTest)
{
  double result = Binomial::binomialTraversal<Binomial::ZubairEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4880
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.4881);
}

TEST(BinomialTest, americanCallZubairTest)
{
  double result = Binomial::binomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.8586
  EXPECT_GE(result, 6.85855);
  EXPECT_LT(result, 6.85865);
}

TEST(BinomialTest, americanCallZubairNoDividendTest)
{
  double result = Binomial::binomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, americanPutZubairTest)
{
  double result = Binomial::binomialTraversal<Binomial::ZubairAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4881
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.48815);
}

// ============= Parallel QuantLib tests ================
TEST(BinomialTest, parEuropeanCallQLTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, parEuropeanCallQLNoDividendTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, parEuropeanPutQLTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::QLEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4880
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.4881);
}

TEST(BinomialTest, parAmericanCallQLTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::QLAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.8586
  EXPECT_GE(result, 6.85855);
  EXPECT_LT(result, 6.85865);
}

TEST(BinomialTest, parAmericanCallQLNoDividendTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::QLAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, parAmericanPutQLTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::QLAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4881
  EXPECT_GE(result, 10.48805);
  EXPECT_LT(result, 10.48815);
}

// =========== Parallel Zubair tests ==============
TEST(BinomialTest, parEuropeanCallZubairTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.7695
  EXPECT_GE(result, 6.76945);
  EXPECT_LT(result, 6.76955);
}

TEST(BinomialTest, parEuropeanCallZubairNoDividendTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, parEuropeanPutZubairTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::ZubairEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4880
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.4881);
}

TEST(BinomialTest, parAmericanCallZubairTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 6.8586
  EXPECT_GE(result, 6.85855);
  EXPECT_LT(result, 6.85865);
}

TEST(BinomialTest, parAmericanCallZubairNoDividendTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);

  // should be approx 7.4510
  EXPECT_GE(result, 7.4505);
  EXPECT_LT(result, 7.4515);
}

TEST(BinomialTest, parAmericanPutZubairTest)
{
  double result = Binomial::parallelBinomialTraversal<Binomial::ZubairAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);

  // should be approx 10.4881
  EXPECT_GE(result, 10.48795);
  EXPECT_LT(result, 10.48815);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
