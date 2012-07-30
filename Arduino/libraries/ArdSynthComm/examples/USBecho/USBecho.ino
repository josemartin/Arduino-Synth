/*
  USBecho
 
 Does an echo on the USART0 (PC) using the ArdSynthComm library, 
 handling directly the ISR from UART0
 
 */

#include <ArdSynthComm.h>

/** ArdSynthComm instace */
ArdSynthComm comm;


volatile byte ReceivedByte = 0; //holds the incoming byte from the receive buffer.

void setup() {
  comm.setupUSB(57600); //Setup the USB interface
}
 

/** Handles the ISR from UART0, and replicates the received byte back. */
ISR(USART0_RX_vect){
  ReceivedByte = UDR0;  
  UDR0 = ReceivedByte;
} 

void loop()  {

}
