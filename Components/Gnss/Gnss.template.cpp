// ======================================================================
// \title  Gnss.cpp
// \author kq9p
// \brief  cpp file for Gnss component implementation class
// ======================================================================

#include "Components/Gnss/Gnss.hpp"

namespace Gnss {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Gnss ::
    Gnss(const char* const compName) :
      GnssComponentBase(compName)
  {

  }

  Gnss ::
    ~Gnss()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for typed input ports
  // ----------------------------------------------------------------------

  void Gnss ::
    gnssRecv_handler(
        FwIndexType portNum,
        Fw::Buffer& recvBuffer,
        const Drv::RecvStatus& recvStatus
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Gnss ::
    gnssEnable_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        Fw::On newStatus
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  // ----------------------------------------------------------------------
  // Implementations for internal state machine actions
  // ----------------------------------------------------------------------

  void Gnss ::
    Gnss_Gnss_nmeaSentence_action_writeChar(
        SmId smId,
        Gnss_Gnss_nmeaSentence::Signal signal
    )
  {
    // TODO
  }

  void Gnss ::
    Gnss_Gnss_nmeaSentence_action_parseSentence(
        SmId smId,
        Gnss_Gnss_nmeaSentence::Signal signal
    )
  {
    // TODO
  }

  void Gnss ::
    Gnss_Gnss_nmeaSentence_action_resetSentence(
        SmId smId,
        Gnss_Gnss_nmeaSentence::Signal signal
    )
  {
    // TODO
  }

}
