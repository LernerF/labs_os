#include <gtest/gtest.h>
#include "utils.hpp"

TEST(UtilsTest, ToUpperCaseBasic) {
    char str1[] = "hello";
    toUpperCase(str1);
    EXPECT_STREQ(str1, "HELLO");

    char str2[] = "Hello World";
    toUpperCase(str2);
    EXPECT_STREQ(str2, "HELLO WORLD");

    char str3[] = "123abc";
    toUpperCase(str3);
    EXPECT_STREQ(str3, "123ABC");
}

TEST(UtilsTest, RemoveDoubleSpacesBasic) {
    char str1[] = "hello   world";
    removeDoubleSpaces(str1);
    EXPECT_STREQ(str1, "hello world");

    char str3[] = "no_spaces_here";
    removeDoubleSpaces(str3);
    EXPECT_STREQ(str3, "no_spaces_here");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}