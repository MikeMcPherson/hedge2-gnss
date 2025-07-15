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
      char m_sentenceBuffer[128] = {0}; //!< Buffer for NMEA sentence
      U32 m_sentencePtr = 0; //!< Current pointer into the sentence buffer
      char m_char = '\0'; //!< Current character being processed
      Gnss_Gnss_nmeaSentence m_nmeaSentenceSM; //!< NMEA sentence state machine

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

    PRIVATE:

      // ----------------------------------------------------------------------
      // Implementations for internal state machine actions
      // ----------------------------------------------------------------------

      //! Implementation for action writeChar of state machine Gnss_Gnss_nmeaSentence
      //!
      //! Action to write the detected character to the sentence buffer
      void Gnss_Gnss_nmeaSentence_action_writeChar(
          SmId smId, //!< The state machine id
          Gnss_Gnss_nmeaSentence::Signal signal //!< The signal
      ) override;

      //! Implementation for action parseSentence of state machine Gnss_Gnss_nmeaSentence
      //!
      //! Action to parse the sentence once confirmed
      void Gnss_Gnss_nmeaSentence_action_parseSentence(
          SmId smId, //!< The state machine id
          Gnss_Gnss_nmeaSentence::Signal signal //!< The signal
      ) override;

      //! Implementation for action resetNmeaSentence of state machine Gnss_Gnss_nmeaSentence
      //!
      //! Action to reset the state machine, clearing any buffers or flags
      void Gnss_Gnss_nmeaSentence_action_resetSentence(
          SmId smId, //!< The state machine id
          Gnss_Gnss_nmeaSentence::Signal signal //!< The signal
      ) override;

  };

}

#endif
