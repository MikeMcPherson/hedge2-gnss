module gnssRpi {

  # ----------------------------------------------------------------------
  # Defaults
  # ----------------------------------------------------------------------

  module Default {
    constant QUEUE_SIZE = 10
    constant STACK_SIZE = 64 * 1024
  }

  # ----------------------------------------------------------------------
  # Active component instances
  # ----------------------------------------------------------------------

  instance blockDrv: Drv.BlockDriver base id 0x0100 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 140

  instance rateGroup1: Svc.ActiveRateGroup base id 0x0200 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 120

  instance rateGroup2: Svc.ActiveRateGroup base id 0x0300 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 119

  instance rateGroup3: Svc.ActiveRateGroup base id 0x0400 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 118

  instance cmdDisp: Svc.CommandDispatcher base id 0x0500 \
    queue size 20 \
    stack size Default.STACK_SIZE \
    priority 101

  instance cmdSeq: Svc.CmdSequencer base id 0x0600 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 100

  instance comQueue: Svc.ComQueue base id 0x0700 \
      queue size Default.QUEUE_SIZE \
      stack size Default.STACK_SIZE \
      priority 100 \

  instance fileDownlink: Svc.FileDownlink base id 0x0800 \
    queue size 30 \
    stack size Default.STACK_SIZE \
    priority 100

  instance fileManager: Svc.FileManager base id 0x0900 \
    queue size 30 \
    stack size Default.STACK_SIZE \
    priority 100

  instance fileUplink: Svc.FileUplink base id 0x0A00 \
    queue size 30 \
    stack size Default.STACK_SIZE \
    priority 100

  instance eventLogger: Svc.ActiveLogger base id 0x0B00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 98

  # comment in Svc.TlmChan or Svc.TlmPacketizer
  # depending on which form of telemetry downlink
  # you wish to use

  instance tlmSend: Svc.TlmChan base id 0x0C00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 97

  #instance tlmSend: Svc.TlmPacketizer base id 0x0C00 \
  #    queue size Default.QUEUE_SIZE \
  #    stack size Default.STACK_SIZE \
  #    priority 97

  instance prmDb: Svc.PrmDb base id 0x0D00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 96

  @ GNSS component instance
  instance gnss: Gnss.Gnss base id 0x0E00 \
  queue size Default.QUEUE_SIZE \
  stack size Default.STACK_SIZE \
  priority 95

# ----------------------------------------------------------------------
  # Queued component instances
  # ----------------------------------------------------------------------

  instance $health: Svc.Health base id 0x2000 \
    queue size 25

  # ----------------------------------------------------------------------
  # Passive component instances
  # ----------------------------------------------------------------------

  @ Communications driver. May be swapped with other com drivers like UART or TCP
  instance comDriver: Drv.TcpServer base id 0x4000

  instance framer: Svc.Framer base id 0x4100

  instance fatalAdapter: Svc.AssertFatalAdapter base id 0x4200

  instance fatalHandler: Svc.FatalHandler base id 0x4300

  @ Buffer manager instance. Configured to use a malloc allocator
  @ and a single buffer bin of size 1024 bytes with 100 buffers.
  @ This can be adjusted based on the application's memory requirements.
  instance bufferManager: Svc.BufferManager base id 0x4400 \
  {
    phase Fpp.ToCpp.Phases.configComponents """
    Fw::MallocAllocator m_allocator;
    Svc::BufferManager::BufferBins bufferManagerBins;
    memset(&bufferManagerBins, 0, sizeof(bufferManagerBins));
    {
      bufferManagerBins.bins[0].bufferSize = 1024;
      bufferManagerBins.bins[0].numBuffers = 100;
      bufferManager.setup(
          200,
          0,
          m_allocator,
          bufferManagerBins
      );
    }
    """
  }

  instance chronoTime: Svc.ChronoTime base id 0x4500

  instance rateGroupDriver: Svc.RateGroupDriver base id 0x4600

  instance textLogger: Svc.PassiveTextLogger base id 0x4800

  instance deframer: Svc.Deframer base id 0x4900

  instance systemResources: Svc.SystemResources base id 0x4A00

  instance comStub: Svc.ComStub base id 0x4B00

  @ UART driver instance. Configured to use a Linux UART driver
  instance uartDrv: Drv.LinuxUartDriver base id 0x0F00 \
  {

    phase Fpp.ToCpp.Phases.configComponents """
      const bool status = uartDrv.open("/dev/ttyUSB0",
          Drv::LinuxUartDriver::BAUD_9600,
          Drv::LinuxUartDriver::NO_FLOW,
          Drv::LinuxUartDriver::PARITY_NONE,
          1024
      );
      if (status) 
      {
        printf("Successfully opened UART driver\\n");
        uartDrv.start();
      } else 
      {
        printf("[ERROR]: Could not open UART driver\\n");
      }
    """

    phase Fpp.ToCpp.Phases.stopTasks """
    uartDrv.quitReadThread();
    """

  }

}
