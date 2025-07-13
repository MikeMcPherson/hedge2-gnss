// ======================================================================
// \title  Gnss.cpp
// \author kq9p
// \brief  cpp file for Gnss component implementation class
//
// The F' component implements a GNSS receiver that processes NMEA sentences.
// It handles GNSS data reception, parsing, and provides commands to enable/disable GNSS
// functionality. The component maintains state variables for GNSS status, fix validity,
// and geographic coordinates. It also provides telemetry outputs for GNSS data.
// ======================================================================

#include "Components/Gnss/Gnss.hpp"
#include "Fw/Logger/Logger.hpp"
#include "Fw/Time/Time.hpp"
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
    m_numSentences = 0; //!< Number of NMEA sentences received
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
	  CNMEAParser	NMEAParser; //!< NMEA Parser instance
    // Create data structures to hold parsed NMEA data
    // These will be used to store the parsed data from the NMEA sentences
    // GGA, GSV, and RMC data structures
    // These structures are defined in the NMEAParserData.h file
    CNMEAParserData::GGA_DATA_T m_ggaData; //!< GGA data structure
    CNMEAParserData::GSV_DATA_T m_gsvData; //!< GSV data structure
    CNMEAParserData::RMC_DATA_T m_rmcData; //!< RMC data structure

    // Is the GNSS enabled?
    if (m_gnssEnabled == Fw::On::ON) {
      // How many bytes were received?
      U32 m_bufferSize = recvBuffer.getSize();
      // Get the data pointer from the buffer
      char* m_data_pointer = reinterpret_cast<char*>(recvBuffer.getData());
      // Check the receive status
      if(recvStatus == Drv::RecvStatus::RECV_OK) {
        // Process the NMEA data
        // Increment the number of sentences received
        m_numSentences++;
        // Update telemetry
        this->tlmWrite_numSentences(m_numSentences);
        // Process the NMEA buffer
        CNMEAParserData::ERROR_E nErr;
        if ((nErr = NMEAParser.ProcessNMEABuffer(m_data_pointer, m_bufferSize)) == CNMEAParserData::ERROR_OK) {
          // Successfully processed the NMEA buffer
          // Retrieve GGA data
          if ((nErr = NMEAParser.GetGNGGA(m_ggaData)) == CNMEAParserData::ERROR_OK) {
            // // If GPS quality has changed, log the event
            // if (static_cast<U32>(m_ggaData.m_nGPSQuality) != m_gpsQuality) {
            //   m_gpsQuality = static_cast<U32>(m_ggaData.m_nGPSQuality);
            //   this->log_ACTIVITY_HI_gpsQuality(m_gpsQuality);
            // }
            // Check to see if we have a fix
            if (static_cast<U32>(m_ggaData.m_nGPSQuality) > 0 && static_cast<U32>(m_ggaData.m_nGPSQuality) < 4) {
              // We have a valid fix
              // If fix status has changed, log the event, then set current fix valid status
              if(m_fixValid != Fw::On::ON) {
                this->log_ACTIVITY_HI_fixValidity(Fw::On::ON);
              }
              m_fixValid = Fw::On::ON;
              // Record the time of the last fix
              Fw::Time(m_seconds, m_microseconds);
              m_lastFixTime = static_cast<F32>(m_seconds) + (static_cast<F32>(m_microseconds) / 1e6f);
              // Update telemetry with GGA data
              this->tlmWrite_latitude(m_ggaData.m_dLatitude);
              this->tlmWrite_longitude(m_ggaData.m_dLongitude);
              this->tlmWrite_altitude(m_ggaData.m_dAltitudeMSL);
              // Store the latitude, longitude, altitude, speed, and heading
              m_latitude = m_ggaData.m_dLatitude;
              m_longitude = m_ggaData.m_dLongitude;
              m_altitude = m_ggaData.m_dAltitudeMSL;
              // Retrieve RMC data
              if ((nErr = NMEAParser.GetGNRMC(m_rmcData)) == CNMEAParserData::ERROR_OK) {
                // Successfully retrieved RMC data
                m_speed = m_rmcData.m_dSpeedKnots;
                m_heading = m_rmcData.m_dTrackAngle;
                // Update telemetry with RMC data
                this->tlmWrite_speed(m_speed);
                this->tlmWrite_heading(m_heading);
              } else
              {
                Fw::Logger::log("Failed to get GNRMC data: %d\n", nErr);
              }
            } else
            {
              // No valid fix
              // Retrieve the current time
              Fw::Time(m_seconds, m_microseconds);
              // If it has been more than 2 seconds since the last fix, log the event and set fix validity to OFF
              m_thisFixTime = static_cast<F32>(m_seconds) + (static_cast<F32>(m_microseconds) / 1e6f);
              if((m_fixValid != Fw::On::OFF) && ((m_thisFixTime - m_lastFixTime) > 2.0f)) {
                this->log_ACTIVITY_HI_fixValidity(Fw::On::OFF);
                m_fixValid = Fw::On::OFF;
              }
            }
          } else {
            Fw::Logger::log("Failed to get GNGGA data: %d\n", nErr);
          }
        } else
        {
          Fw::Logger::log("NMEA Parser ProcessNMEABuffer Failed and returned error: %d\n", nErr);
        }
      } else if(recvStatus == Drv::RecvStatus::RECV_NO_DATA) 
      {
        // Handle no data case
        Fw::Logger::log("No data received on port %d\n", portNum);
      } else {
        // Handle error case
        Fw::Logger::log("Receive error on port %d, recvStatus: %d\n", portNum, recvStatus);
      }
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
        U32 cmdSeq,
        Fw::On newStatus
    )
  {
    // Save the new GNSS enabled status
    m_gnssEnabled = newStatus;
    if(m_gnssEnabled == Fw::On::OFF) {
      // Reset to default values when GNSS is disabled
      // And update telemetry and logs
      m_seconds = 0; // Reset seconds
      m_microseconds = 0; // Reset microseconds
      m_lastFixTime = 0.0; // Reset last fix time
      m_gpsQuality = 0; // Reset GPS quality
      this->log_ACTIVITY_HI_gpsQuality(m_gpsQuality); // Log GPS quality
      m_fixValid = Fw::On::OFF; // Reset fix validity
      this->log_ACTIVITY_HI_fixValidity(m_fixValid); // Log fix validity
      m_numSentences = 0; // Reset the number of sentences
      this->tlmWrite_numSentences(m_numSentences); // Update telemetry
      m_latitude = 0.0; // Reset latitude
      this->tlmWrite_latitude(m_latitude); // Update telemetry
      m_longitude = 0.0; // Reset longitude
      this->tlmWrite_longitude(m_longitude); // Update telemetry
      m_altitude = 0.0; // Reset altitude
      this->tlmWrite_altitude(m_altitude); // Update telemetry
      m_speed = 0.0; // Reset speed
      this->tlmWrite_speed(m_speed); // Update telemetry
      m_heading = 0.0; // Reset heading
      this->tlmWrite_heading(m_heading); // Update telemetry
    }
    // Log the GNSS state change
    this->log_ACTIVITY_HI_gnssState(m_gnssEnabled);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
