// ======================================================================
// \title  GnssTester.hpp
// \author kq9p
// \brief  hpp file for Gnss component test harness implementation class
// ======================================================================

#ifndef Gnss_GnssTester_HPP
#define Gnss_GnssTester_HPP

#include "Components/Gnss/GnssGTestBase.hpp"
#include "Components/Gnss/Gnss.hpp"

namespace Gnss {

  class GnssTester :
    public GnssGTestBase
  {

    public:

      // ----------------------------------------------------------------------
      // Constants
      // ----------------------------------------------------------------------

      // Maximum size of histories storing events, telemetry, and port outputs
      static const FwSizeType MAX_HISTORY_SIZE = 10;

      // Instance ID supplied to the component instance under test
      static const FwEnumStoreType TEST_INSTANCE_ID = 0;

      // Queue depth supplied to the component instance under test
      static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;

    public:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object GnssTester
      GnssTester();

      //! Destroy object GnssTester
      ~GnssTester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      void toDo();

    private:

      // ----------------------------------------------------------------------
      // Helper functions
      // ----------------------------------------------------------------------

      //! Connect ports
      void connectPorts();

      //! Initialize components
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Member variables
      // ----------------------------------------------------------------------

      //! The component under test
      Gnss component;

  };

}

#endif
