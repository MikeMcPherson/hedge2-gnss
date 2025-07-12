// ======================================================================
// \title  Gnss.hpp
// \author kq9p
// \brief  hpp file for Gnss component implementation class
// ======================================================================

#ifndef Gnss_Gnss_HPP
#define Gnss_Gnss_HPP

#include "Components/Gnss/GnssComponentAc.hpp"

namespace Gnss {

  class Gnss :
    public GnssComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Gnss object
      Gnss(
          const char* const compName //!< The component name
      );

      //! Destroy Gnss object
      ~Gnss();

      U32 m_numSentences = 0; //!< Number of sentences received
      U32 m_gpsQuality = 0; //!< GPS quality indicator
      Fw::On m_gnssEnabled = Fw::On::OFF; //!< GNSS enabled flag
      Fw::On m_fixValid = Fw::On::OFF; //!< Valid fix flag
      U32 m_seconds = 0;
      U32 m_microseconds = 0;
      F32 m_lastFixTime = 0.0;
      F32 m_thisFixTime = 0.0;
      F32 m_latitude = 0.0; //!< Latitude in degrees
      F32 m_longitude = 0.0; //!< Longitude in degrees
      F32 m_altitude = 0.0; //!< Altitude in meters
      F32 m_speed = 0.0; //!< Speed in meters per second
      F32 m_heading = 0.0; //!< Heading in degrees

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for gnssRecv
      void gnssRecv_handler(
          FwIndexType portNum, //!< The port number
          Fw::Buffer& recvBuffer,
          const Drv::RecvStatus& recvStatus
      ) override;

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command gnssEnable
      //!
      //! GNSS enable command
      void gnssEnable_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          Fw::On newStatus
      ) override;

  };

}

#endif
