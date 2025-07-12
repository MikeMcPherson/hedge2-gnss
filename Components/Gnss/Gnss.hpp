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
      bool m_validFix = false; //!< Valid fix flag

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
          U32 cmdSeq //!< The command sequence number
      ) override;

  };

}

#endif
