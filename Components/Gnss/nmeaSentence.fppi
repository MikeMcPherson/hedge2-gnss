@ State machine for processing NMEA sentences in GNSS components
@ nmeaSentence is a simple parser that only detects the start and end of sentences
@ It does not parse the content of the sentences, which is handled by the Gnss component
state machine nmeaSentence {

#
# Signals
#

  @ "G" detected, might be the start of a sentence
  signal gDetected: string size 1

  @ Carriage return detected, might be the end of a sentence
  signal crDetected: string size 1

  @ New line detected, might be the end of a sentence
  signal nlDetected: string size 1

  @ Any character detected that is not "G", carriage return, or newline
  signal otherDetected: string size 1

  @ Returns true for any character
  signal noOp

#
# Actions
#

  @ Action to write the detected character to the sentence buffer
  action writeChar

  @ Action to parse the sentence once confirmed
  action parseSentence

  @ Action to reset the state machine, clearing any buffers or flags
  action resetNmeaSentence

#
# Initial state, first resetting the state machine
#

initial enter START_WAITING

#
# States
#
  
  @ No sentence detected, waiting for start of sentence
  state START_WAITING {
    @ Initialize the state machine, clearing any buffers
    entry do { resetNmeaSentence }
    @ Transition to START_CANDIDATE on "G" detection
    on gDetected enter START_CANDIDATE
    @ Write the detected character to the buffer
    exit do { writeChar }
  }

  @ Initial "G" has been detected, waiting for confirmation
  state START_CANDIDATE {
    @ Transition to START_CONFIRMED on second "G" detection
    on gDetected do { writeChar } enter START_CONFIRMED
    @ Next character wasn't "G", go back to waiting for start
    on otherDetected enter START_WAITING
  }

  @ Second "G" has been detected, confirming the start of a sentence
  state START_CONFIRMED {
    @ Transition to END_CANDIDATE on carriage return detection
    on crDetected enter END_CANDIDATE
    @ Write the detected character to the buffer
    exit do { writeChar }
  }

  @ Carriage return detected, waiting for end of sentence confirmation
  state END_CANDIDATE {
    @ Transition to END_CONFIRMED on new line detection
    on nlDetected do { writeChar } enter END_CONFIRMED
    @ Next character wasn't newline, go back to waiting for start
    on otherDetected enter START_WAITING
  }

  @ Newline detected, confirming the end of a sentence
  state END_CONFIRMED {
    @ Compete sentence received, send it to the parser
    entry do { writeChar, parseSentence }
    @ Return to START_WAITING after processing
    on noOp enter START_WAITING
  }

}