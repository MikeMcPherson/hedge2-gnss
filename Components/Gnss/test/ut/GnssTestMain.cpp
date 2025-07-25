// ======================================================================
// \title  GnssTestMain.cpp
// \author kq9p
// \brief  cpp file for Gnss component test main function
// ======================================================================

#include "GnssTester.hpp"

TEST(Nominal, testEnable) {
  Gnss::GnssTester tester;
  tester.testEnable();
}

TEST(Nominal, testLatitude) {
  Gnss::GnssTester tester;
  tester.testLatitude();
}

TEST(Nominal, testLongitude) {
  Gnss::GnssTester tester;
  tester.testLongitude();
}

TEST(Nominal, testAltitude) {
  Gnss::GnssTester tester;
  tester.testAltitude();
}

TEST(Nominal, testGpsQuality) {
  Gnss::GnssTester tester;
  tester.testGpsQuality();
}

TEST(Nominal, testSpeed) {
  Gnss::GnssTester tester;
  tester.testSpeed();
}

TEST(Nominal, testHeading) {
  Gnss::GnssTester tester;
  tester.testHeading();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
