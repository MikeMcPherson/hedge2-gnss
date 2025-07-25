// ======================================================================
// \title  GnssTester.cpp
// \author kq9p
// \brief  cpp file for Gnss component test harness implementation class
// ======================================================================

#include "GnssTester.hpp"

#define TESTGGASENTENCE "$GNGGA,210230,3845.0000,N,09430.0000,W,1,07,1.1,370.5,M,-29.5,M,,*6D\r\n"
#define TESTRMCSENTENCE "$GNRMC,210230,A,3845.0000,N,09430.0000,W,250.0,076.5,130495,003.8,E*7E\r\n"

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
    testGnssEnable_cmdHandler()
  {
    // Test enabling the GNSS component
    const U32 cmdSeq = 10; //!< Arbitrary command sequence number

    // Test the command to enable GNSS
    this->sendCmd_gnssEnable(
        0,
        cmdSeq, // Command sequence number
        Fw::On::ON // Enable GNSS
    ); // Queue the command
    this->component.doDispatch(); // Dispatch the command
    ASSERT_CMD_RESPONSE_SIZE(1); // Assert that one command response was generated
    ASSERT_CMD_RESPONSE(0, GnssComponentBase::OPCODE_GNSSENABLE, cmdSeq, Fw::CmdResponse::OK); // Assert that the command response is OK
  }

  void GnssTester ::
    testGnssRecv_handler_Gga()
  {
    const U32 cmdSeq = 10; //!< Arbitrary command sequence number
    U8 m_testGgaSentence[] = TESTGGASENTENCE; // Example NMEA sentence with latitude
    Fw::Buffer recvBuffer;
    recvBuffer.setData(m_testGgaSentence); // Example NMEA sentence
    recvBuffer.setSize(sizeof(m_testGgaSentence)); // Set the size of the buffer
    this->sendCmd_gnssEnable(
        0,
        cmdSeq, // Command sequence number
        Fw::On::ON // Enable GNSS
    ); // Enable so Gnss will process the NMEA sentence
    this->component.doDispatch();
    this->invoke_to_gnssRecv(0, recvBuffer, Drv::RecvStatus::RECV_OK); // Invoke the gnssRecv handler with the test data
    this->component.doDispatch();
    ASSERT_TLM_latitude_SIZE(1);
    ASSERT_TLM_latitude(0, 38.75); // Assert that the latitude is as expected
    ASSERT_TLM_longitude_SIZE(1);
    ASSERT_TLM_longitude(0, -94.5); // Assert that the longitude is as expected
    ASSERT_TLM_altitude_SIZE(1);
    ASSERT_TLM_altitude(0, 370.5);
    ASSERT_EVENTS_fixValidity_SIZE(1);
    ASSERT_EVENTS_fixValidity(0, Fw::On::ON); // Assert that the fix validity is ON
  }

  void GnssTester ::
    testGnssRecv_handler_Rmc()
  {
    const U32 cmdSeq = 10; //!< Arbitrary command sequence number
    U8 m_testRmcSentence[] = TESTRMCSENTENCE; // Example RMC sentence
    Fw::Buffer recvBuffer;
    recvBuffer.setData(m_testRmcSentence); // Example RMC sentence
    recvBuffer.setSize(sizeof(m_testRmcSentence)); // Set the size of the buffer
    this->sendCmd_gnssEnable(
        0,
        cmdSeq, // Command sequence number
        Fw::On::ON // Enable GNSS
    ); // Enable so Gnss will process the NMEA sentence
    this->component.doDispatch();
    this->invoke_to_gnssRecv(0, recvBuffer, Drv::RecvStatus::RECV_OK); // Invoke the gnssRecv handler with the test data
    this->component.doDispatch();
    ASSERT_TLM_speed_SIZE(1);
    ASSERT_TLM_speed(0, 250.0);
    ASSERT_TLM_heading_SIZE(1);
    ASSERT_TLM_heading(0, 76.5);
  }

}
