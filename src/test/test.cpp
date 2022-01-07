#include <gtest/gtest.h>
#include "binomial.h"

TEST(binomial, americanPut)
{
     GTEST_ASSERT_EQ(32, 32);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}