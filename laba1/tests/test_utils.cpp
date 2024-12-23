#include <gtest/gtest.h>
#include "utils.hpp"

TEST(UtilsTest, ToUpperCase) {
    char str1[] = "hello world";
    toUpperCase(str1);
    EXPECT_STREQ(str1, "HELLO WORLD");

    char str2[] = "Google Test";
    toUpperCase(str2);
    EXPECT_STREQ(str2, "GOOGLE TEST");

    char str3[] = "123 !@#";
    toUpperCase(str3);
    EXPECT_STREQ(str3, "123 !@#");  // Цифры и спецсимволы не изменяются
}

TEST(UtilsTest, RemoveDoubleSpaces) {
    char str1[] = "hello   world";
    removeDoubleSpaces(str1);
    EXPECT_STREQ(str1, "hello world");

    char str2[] = "a    b c     d";
    removeDoubleSpaces(str2);
    EXPECT_STREQ(str2, "a b c d");

    char str3[] = "NoExtraSpaces";
    removeDoubleSpaces(str3);
    EXPECT_STREQ(str3, "NoExtraSpaces"); 
}

TEST(UtilsTest, EmptyString) {
    char str[] = "";
    toUpperCase(str);
    EXPECT_STREQ(str, ""); 

    removeDoubleSpaces(str);
    EXPECT_STREQ(str, ""); 
}

TEST(UtilsTest, LeadingAndTrailingSpaces) {
    char str[] = "   multiple   spaces   ";
    removeDoubleSpaces(str);
    EXPECT_STREQ(str, " multiple spaces "); 
}