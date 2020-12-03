// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>

#include "Parser.hpp"
#include <gtest/gtest.h>

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }
TEST(Parser, PathToFile) {
    Parser A("/Users/nishaque/Desktop/33/С++/lab-04-boost-filesystem/ftp");
    std::cout << "broker:" << A.getBroker("00001024");
    ASSERT_EQ(A.getBroker("00001024"), "alpha");
}
TEST(Parser, EmptyPathToFile) {
    Parser A("");
    ASSERT_EQ(A.getBroker("00001024"), "");
}
