// ======================================================================
// \title  GnssTestMain.cpp
// \author kq9p
// \brief  cpp file for Gnss component test main function
// ======================================================================

#include "GnssTester.hpp"

TEST(Nominal, toDo) {
  Gnss::GnssTester tester;
  tester.toDo();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
