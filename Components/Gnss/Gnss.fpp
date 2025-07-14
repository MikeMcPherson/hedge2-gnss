module Gnss {
    @ GNSS read, parse, and propagate
    active component Gnss {
        include "nmeaSentence.fppi"

        # One async command/port is required for active components
        @ GNSS enable command
        async command gnssEnable(newStatus: Fw.On) opcode 0

        @ Count the number of NMEA sentences received
        telemetry numSentences: U32
        @ GGA latitude
        telemetry latitude: F64
        @ GGA longitude
        telemetry longitude: F64
        @ GGA altitude
        telemetry altitude: F64
        @ RMC speed
        telemetry speed: F64
        @ RMC course
        telemetry heading: F64

        @ GNSS receiver state: enabled or disabled
        event gnssState(enabled: Fw.On) severity activity high id 1 format "GNSS state changed to: {}"
        @ GNSS fix validity: valid or invalid
        event fixValidity(valid: Fw.On) severity activity high id 2 format "GNSS fix validity changed to: {}"
        @ GPS quality: 0 = no fix, 1 = GPS fix, 2 = DGPS fix, etc.
        event gpsQuality(quality: U32) severity activity high id 3 format "GPS quality changed to: {}"

        @ Port to receive GNSS data
        async input port gnssRecv: Drv.ByteStreamRecv
        @ Port to send GNSS commands
        output port gnssSend: Drv.ByteStreamSend
        @ Port to return buffers for deallocation
        output port deallocate: Fw.BufferSend

        # @ Example parameter
        # param PARAMETER_NAME: U32

        @ State machine for processing NMEA sentences
        state machine instance m_nmeaSentence: nmeaSentence

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}