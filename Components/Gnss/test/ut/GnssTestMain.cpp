// ======================================================================
// \title  GnssTestMain.cpp
// \author kq9p
// \brief  cpp file for Gnss component test main function
// ======================================================================

#include "GnssTester.hpp"

TEST(Nominal, testGnssEnable_cmdHandler) {
  Gnss::GnssTester tester;
  tester.testGnssEnable_cmdHandler();
}

TEST(Nominal, testGnssRecv_handler_Gga) {
  Gnss::GnssTester tester;
  tester.testGnssRecv_handler_Gga();
}

TEST(Nominal, testGnssRecv_handler_Rmc) {
  Gnss::GnssTester tester;
  tester.testGnssRecv_handler_Rmc();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
