
#include <gtest/gtest.h>

#include "bitwise_tasks.cpp"

TEST(BitwiseSimplest, simplest)
{
}


TEST(BitwiseCheckBit, checkBit1)
{
    unsigned int  number = 9;
    int idx = 2;

    EXPECT_EQ(0, getBitAtIndex(number, idx));
}
