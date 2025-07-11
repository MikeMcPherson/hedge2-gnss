// ======================================================================
// \title  Gnss.cpp
// \author kq9p
// \brief  cpp file for Gnss component implementation class
// ======================================================================

#include "Components/Gnss/Gnss.hpp"
#include "Fw/Logger/Logger.hpp"

namespace Gnss {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Gnss ::
    Gnss(const char* const compName) :
      GnssComponentBase(compName)
  {
    m_numSentences = 0;
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
    int m_status = 0;
    U32 m_bufferSize = recvBuffer.getSize();
    char* m_data_pointer = reinterpret_cast<char*>(recvBuffer.getData());
    if(recvStatus == Drv::RecvStatus::RECV_OK) {
      m_numSentences++;
      this->tlmWrite_numSentences(m_numSentences);
      // Process the received data
      // For example, gnss it back
      // this->gnssSend_out(0, recvBuffer);
      // Fw::Logger::log(
      //     "Received data: %.*s\n",
      //     m_bufferSize,
      //     m_data_pointer
      // );
    } else if(recvStatus == Drv::RecvStatus::RECV_NO_DATA) {
      // Handle no data case
      m_status = 1; // No data received
    } else {
      // Handle error case
      m_status = -1; // Error occurred
    }
    this->deallocate_out(0, recvBuffer);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Gnss ::
    gnssEnable_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
