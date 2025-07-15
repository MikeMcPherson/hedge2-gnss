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

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for gnssRecv
      //!
      //! Port to receive GNSS data
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

      //! Implementation for action resetSentence of state machine Gnss_Gnss_nmeaSentence
      //!
      //! Action to reset the state machine, clearing any buffers or flags
      void Gnss_Gnss_nmeaSentence_action_resetSentence(
          SmId smId, //!< The state machine id
          Gnss_Gnss_nmeaSentence::Signal signal //!< The signal
      ) override;

  };

}

#endif
