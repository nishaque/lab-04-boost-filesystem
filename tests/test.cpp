// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>

#include "Parser.hpp"
#include <gtest/gtest.h>

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }
TEST(Parser, PathToFile) {
    Parser A("/home/travis/build/nishaque/lab-04-boost-filesystem//ftp");
    std::cout << "broker:" << A.getBroker("00001024");
    ASSERT_EQ(A.getBroker("00001024"), "alpha");
}
TEST(Parser, Printing) {
  std::ostringstream output;
  Parser A("/home/travis/build/nishaque/lab-04-boost-filesystem//ftp");
  output << A;
  EXPECT_EQ(output.str(),
            R"(alpha balance_00001024_20191811.txt
ib balance_00001222_20201903.txt
bsc balance_00001234_20181001.txt
bsc balance_00001234_20171410.txt
ib balance_00001794_20200101.txt
ib balance_00001794_20191412.txt
ib balance_00003324_20200703.txt
mts balance_00003333_20201811.txt
vtb balance_00005555_20161811.txt
bsc balance_00053474_20201001.txt
bsc balance_00061204_20191402.txt
bsc balance_00561204_20191404.txt
broker: alpha account: 00001024 files: 1 lastdate: 20191811
broker: ib account: 00001222 files: 1 lastdate: 20201903
broker: bsc account: 00001234 files: 2 lastdate: 20181001
broker: ib account: 00001794 files: 2 lastdate: 20200101
broker: ib account: 00003324 files: 1 lastdate: 20200703
broker: mts account: 00003333 files: 1 lastdate: 20201811
broker: vtb account: 00005555 files: 1 lastdate: 20161811
broker: bsc account: 00053474 files: 1 lastdate: 20201001
broker: bsc account: 00061204 files: 1 lastdate: 20191402
broker: bsc account: 00561204 files: 1 lastdate: 20191404
)");
}
