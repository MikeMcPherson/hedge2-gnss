@ State machine for processing NMEA sentences in GNSS components
@ nmeaSentence is a simple parser that only detects the start and end of sentences
@ It does not parse the content of the sentences, which is handled by the Gnss component
state machine nmeaSentence {

#
# Signals
#

  @ "$" detected, might be the start of a sentence
  signal dollarDetected

  @ "G" detected, might be the start of a sentence
  signal gDetected

  @ Carriage return detected, might be the end of a sentence
  signal crDetected

  @ New line detected, might be the end of a sentence
  signal nlDetected

  @ Returns true for any character
  signal noOp

  # @ Takes the next character from the input stream
  # @ and processes it.
  signal nextChar: string

#
# Actions
#

  @ Action to write the detected character to the sentence buffer
  action writeChar

  @ Action to parse the sentence once confirmed
  action parseSentence

  @ Action to reset the state machine, clearing any buffers or flags
  action resetSentence

#
# Initial state, first resetting the state machine
#

initial enter NO_SENTENCE

#
# States
#
  
  @ No sentence detected, waiting for start of sentence
  state NO_SENTENCE {
    @ Initialize the state machine, clearing any buffers
    entry do { resetSentence }
    @ Transition to GOT_DOLLAR on "$" detection
    on dollarDetected do { writeChar } enter GOT_DOLLAR
  }

  @ Initial "$" has been detected, waiting for confirmation
  state GOT_DOLLAR {
    @ Transition to GOT_FIRST_G on "G" detection
    on gDetected do { writeChar } enter GOT_FIRST_G
    @ Next character wasn't "G", go back to waiting for start
    on noOp enter NO_SENTENCE
  }

  @ Initial "G" has been detected, waiting for confirmation
  state GOT_FIRST_G {
    @ Transition to GOT_SECOND_G on "G" detection
    on gDetected do { writeChar } enter GOT_SECOND_G
    @ Next character wasn't "G", go back to waiting for start
    on noOp enter NO_SENTENCE
  }

  @ Second "G" has been detected, confirming the start of a sentence
  state GOT_SECOND_G {
    @ Transition to GOT_CR on carriage return detection
    on crDetected do { writeChar } enter GOT_CR
    @ For everything except carriage return, write the character
    @ and stay in the same state
    on noOp do { writeChar } enter GOT_SECOND_G
  }

  @ Carriage return detected, waiting for end of sentence confirmation
  state GOT_CR {
    @ Transition to GOT_NL on newline detection
    on nlDetected do { writeChar } enter GOT_NL
    @ Next character wasn't newline, go back to waiting for start
    on noOp enter NO_SENTENCE
  }

  @ Newline detected, confirming the end of a sentence
  state GOT_NL {
    @ Compete sentence received, send it to the parser
    entry do { writeChar, parseSentence }
    @ Return to NO_SENTENCE after processing
    on noOp enter NO_SENTENCE
  }

}