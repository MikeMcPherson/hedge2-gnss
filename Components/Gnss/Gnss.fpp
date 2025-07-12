module Gnss {
    @ GNSS read, parse, and propagate
    active component Gnss {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ GNSS enable command
        async command gnssEnable(newStatus: Fw.On) opcode 0

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64
        telemetry numSentences: U32
        telemetry latitude: F64
        telemetry longitude: F64
        telemetry altitude: F64
        telemetry speed: F64
        telemetry heading: F64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"
        event gnssState(enabled: Fw.On) severity activity high id 1 format "GNSS state changed to: {}"
        event fixValidity(valid: Fw.On) severity activity high id 2 format "GNSS fix validity changed to: {}"
        event gpsQuality(quality: U32) severity activity high id 3 format "GPS quality changed to: {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched
        async input port gnssRecv: Drv.ByteStreamRecv
        output port gnssSend: Drv.ByteStreamSend
        output port deallocate: Fw.BufferSend

        # @ Example parameter
        # param PARAMETER_NAME: U32

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