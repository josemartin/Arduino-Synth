/*
  MIDI replicator
 
 Replicates the MIDI messages throught USART1 on the USART0 (PC) using the ArdSynthComm library, 
 handling directly the ISR from UART1
 
 */

#include <ArdSynthComm.h>

/** ArdSynth instace */
ArdSynthComm comm;


volatile byte ReceivedByte = 0; //holds the incoming byte from the receive buffer.

void setup() {
  comm.setupUSB(57600); //Setup the USB interface
  comm.setupMIDI();
}
 

/** Handles the ISR from UART1, and replicates the received byte on the USART0. */
ISR(USART1_RX_vect){
  ReceivedByte = UDR1;  
  UDR0 = ReceivedByte;
} 

void loop()  {

}
