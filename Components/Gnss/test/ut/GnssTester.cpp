// ======================================================================
// \title  GnssTester.cpp
// \author kq9p
// \brief  cpp file for Gnss component test harness implementation class
// ======================================================================

#include "GnssTester.hpp"

namespace Gnss {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  GnssTester ::
    GnssTester() :
      GnssGTestBase("GnssTester", GnssTester::MAX_HISTORY_SIZE),
      component("Gnss")
  {
    this->initComponents();
    this->connectPorts();
  }

  GnssTester ::
    ~GnssTester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void GnssTester ::
    toDo()
  {
    // TODO
  }

}
