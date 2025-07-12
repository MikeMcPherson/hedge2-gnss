// ======================================================================
// \title  Gnss.cpp
// \author kq9p
// \brief  cpp file for Gnss component implementation class
// ======================================================================

#include "Components/Gnss/Gnss.hpp"
#include "Fw/Logger/Logger.hpp"
#include "lib/NMEAParserLib/NMEAParser.h"
#include "lib/NMEAParserLib/NMEAParserData.h"

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
	  CNMEAParser	NMEAParser;
    CNMEAParserData::GGA_DATA_T m_ggaData;

    if(recvStatus == Drv::RecvStatus::RECV_OK) {
      m_numSentences++;
      this->tlmWrite_numSentences(m_numSentences);
      CNMEAParserData::ERROR_E nErr;
      if ((nErr = NMEAParser.ProcessNMEABuffer(m_data_pointer, m_bufferSize)) == CNMEAParserData::ERROR_OK) {
        if ((nErr = NMEAParser.GetGNGGA(m_ggaData)) == CNMEAParserData::ERROR_OK) {
          // Check to see if we have a fix
          m_gpsQuality = static_cast<U32>(m_ggaData.m_nGPSQuality);
          if (m_gpsQuality > 0 && m_gpsQuality < 4) {
            // We have a valid fix
            if(m_fixValid != Fw::On::ON) {
              this->log_ACTIVITY_HI_fixValidity(Fw::On::ON);
            }
            m_fixValid = Fw::On::ON;
            this->tlmWrite_latitude(m_ggaData.m_dLatitude);
            this->tlmWrite_longitude(m_ggaData.m_dLongitude);
            this->tlmWrite_altitude(m_ggaData.m_dAltitudeMSL);
            Fw::Logger::log("Received GNGGA data: Sec: %d, Lat: %f, Lon: %f, Alt: %f, Quality: %d\n",
                            m_ggaData.m_nSecond, m_ggaData.m_dLatitude, m_ggaData.m_dLongitude, m_ggaData.m_dAltitudeMSL, m_gpsQuality);
          } else
          {
            // No valid fix
            // TODO how to handle all the GGA/GSA/RMC calls that return zeros
            // TODO separate sentence processing from data retrieval and processing?
            // if(m_fixValid != Fw::On::OFF) {
            //   this->log_ACTIVITY_HI_fixValidity(Fw::On::OFF);
            // }
            // m_fixValid = Fw::On::OFF;
          }
        } else {
          Fw::Logger::log("Failed to get GNGGA data: %d\n", nErr);
        }
      } else
      {
        Fw::Logger::log("NMEA Parser ProcessNMEABuffer Failed and returned error: %d\n", nErr);
      }
    } else if(recvStatus == Drv::RecvStatus::RECV_NO_DATA) {
      // Handle no data case
      m_status = 1; // No data received
    } else {
      // Handle error case
      m_status = -1; // Error occurred
    }

    
    // Return the buffer to the deallocate port
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
