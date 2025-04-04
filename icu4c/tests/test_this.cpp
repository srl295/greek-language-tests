#include <gtest/gtest.h>

TEST(NullTest, test_NOTHING)
{
    ASSERT_TRUE(true);
}

GTEST_API_ int
main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
