// ======================================================================
// \title  Gnss.hpp
// \author kq9p
// \brief  hpp file for Gnss component implementation class
// 
// The F' component implements a GNSS receiver that processes NMEA sentences.
// It handles GNSS data reception, parsing, and provides commands to enable/disable GNSS
// functionality. The component maintains state variables for GNSS status, fix validity,
// and geographic coordinates. It also provides telemetry outputs for GNSS data.
// ======================================================================

#ifndef Gnss_Gnss_HPP
#define Gnss_Gnss_HPP

#include "Components/Gnss/GnssComponentAc.hpp"
#include "lib/NMEAParserLib/NMEAParser.h"
#include "lib/NMEAParserLib/NMEAParserData.h"

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

    PRIVATE:

      CNMEAParserData::GGA_DATA_T m_ggaData; //!< GGA data structure
      CNMEAParserData::GSV_DATA_T m_gsvData; //!< GSV data structure
      CNMEAParserData::RMC_DATA_T m_rmcData; //!< RMC data structure
      char m_sentenceBuffer[128] = {0}; //!< Buffer for NMEA sentences
      U32 m_sentenceBufferIndex = 0; //!< Pointer to the current position in the sentence buffer
      U32 m_numSentences = 0; //!< Number of sentences received
      U32 m_gpsQuality = 0; //!< GPS quality indicator
      Fw::On m_gnssEnabled = Fw::On::OFF; //!< GNSS enabled flag
      Fw::On m_fixValid = Fw::On::OFF; //!< Valid fix flag
      U32 m_seconds = 0; //!< Seconds since  
      U32 m_microseconds = 0; //!< Microseconds 
      F32 m_lastFixTime = 0.0; //!< Last fix time
      F32 m_thisFixTime = 0.0; //!< This fix time
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
          Fw::Buffer& recvBuffer, //!< The received buffer
          const Drv::RecvStatus& recvStatus //!< The receive status
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
          Fw::On newStatus //!< The new status to set
      ) override;

  };

}

#endif
