#include "gtest/gtest.h"
#include "bitmanip.hpp"

TEST(BitManipulation, BitAdditionSimple){
    bits b = {0};
    auto result = add(b, 1);
    ASSERT_EQ(result, (bits{1}));
    
    result = add(bits{1}, 1);
    ASSERT_EQ(result, (bits{1, 0}));
}

TEST(BitManipulation, BitAddition){
    ASSERT_EQ(add(bits{0, 0}, 1), (bits{0, 1}));
    ASSERT_EQ(add(bits{0, 1}, 1), (bits{1, 0}));
    ASSERT_EQ(add(bits{1, 0}, 1), (bits{1, 1}));
    ASSERT_EQ(add(bits{1, 1}, 1), (bits{1, 0, 0}));

    ASSERT_EQ(add(bits{0, 0}, 0), (bits{0, 0}));
    ASSERT_EQ(add(bits{0, 1}, 0), (bits{0, 1}));
    ASSERT_EQ(add(bits{1, 0}, 0), (bits{1, 0}));
    ASSERT_EQ(add(bits{1, 1}, 0), (bits{1, 1}));
}

TEST(BitManipulation, BitAddition3Bits){
    ASSERT_EQ(add(bits{0, 0, 0}, 1), (bits{0, 0, 1}));
    ASSERT_EQ(add(bits{0, 0, 1}, 1), (bits{0, 1, 0}));
    ASSERT_EQ(add(bits{0, 1, 0}, 1), (bits{0, 1, 1}));
    ASSERT_EQ(add(bits{0, 1, 1}, 1), (bits{1, 0, 0}));
    ASSERT_EQ(add(bits{1, 0, 0}, 1), (bits{1, 0, 1}));
    ASSERT_EQ(add(bits{1, 0, 1}, 1), (bits{1, 1, 0}));
    ASSERT_EQ(add(bits{1, 1, 0}, 1), (bits{1, 1, 1}));
    ASSERT_EQ(add(bits{1, 1, 1}, 1), (bits{1, 0, 0, 0}));

    ASSERT_EQ(add(bits{0, 0, 0}, 0), (bits{0, 0, 0}));
    ASSERT_EQ(add(bits{0, 0, 1}, 0), (bits{0, 0, 1}));
    ASSERT_EQ(add(bits{0, 1, 0}, 0), (bits{0, 1, 0}));
    ASSERT_EQ(add(bits{0, 1, 1}, 0), (bits{0, 1, 1}));
    ASSERT_EQ(add(bits{1, 0, 0}, 0), (bits{1, 0, 0}));
    ASSERT_EQ(add(bits{1, 0, 1}, 0), (bits{1, 0, 1}));
    ASSERT_EQ(add(bits{1, 1, 0}, 0), (bits{1, 1, 0}));
    ASSERT_EQ(add(bits{1, 1, 1}, 0), (bits{1, 1, 1}));

    ASSERT_EQ(add(bits{1}, 1), (bits{1, 0}));

}

TEST(BitManipulation, LeftShift){
    ASSERT_EQ(left_shift(bits{1}, 0), (bits{1}));
    ASSERT_EQ(left_shift(bits{1}, 1), (bits{1, 0}));
    ASSERT_EQ(left_shift(bits{1}, 2), (bits{1, 0, 0}));
    ASSERT_EQ(left_shift(bits{1}, 3), (bits{1, 0, 0, 0}));
    ASSERT_EQ(left_shift(bits{1, 1, 0, 1}, 3), (bits{1, 1, 0, 1, 0, 0, 0}));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}