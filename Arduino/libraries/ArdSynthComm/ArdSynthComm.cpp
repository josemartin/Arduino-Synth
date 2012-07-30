/*
  ArdSynthComm.cpp - Library used to configure low level settings of the Arduino Synth communications
  Setups the MIDI port communication using UART1 and USB communication using UART0 (builtin AtMega8U2).
  For use with Arduino Mega (AtMega 2560 or equivalent).
  
  Uses code form user ohnoezitasploded from Arduino official forums.
  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1236223363
  
  Version 1.0 April 24th, 2012
  J. Martin, S. Lopez
*/

#include "ArdSynthComm.h"

/* Used to store the CPU speed used to calculate USART prescaler */
unsigned long clockspeed = F_CPU;





void ArdSynthComm::setupMIDI()
{
  /* The baud prescale that will be loaded into the
*  UBRR1H and UBRR1L registers to set the USART baud rate */
  unsigned long baudprescale;    
  unsigned long baudMIDI = MIDIbaudRate;
  baudprescale = (((clockspeed / (baudMIDI * 16UL))) - 1); //

  cli();  //disable interrupts while initializing the USART
  
  
  /* set transfer complete flag (TXC0 = 1).
  *  clear Frame Error flag (FE0 = 0).  
  *  clear Data overrun flag (DOR0 = 0).
  *  clear Parity overrun flag (UPE0 = 0).
  *  disable doubling of USART transmission speed (U2X0 = 0).  
  *  Disable Multi-Processor Communication Mode-- whatever that is. (MCPM0 = 0)  */
  sbi(UCSR1A, TXC1);
  cbi(UCSR1A, FE1);
  cbi(UCSR1A, DOR1);
  cbi(UCSR1A, UPE1);
  cbi(UCSR1A, U2X1); 
  cbi(UCSR1A, MPCM1);
  

  /* Enable Receive Interrupt (RXCIE0 = 1).
  *  Disable Tranmission Interrupt (TXCIE = 0).
  *  Disable Data Register Empty interrupt (UDRIE0 = 0).
  *  Enable reception (RXEN0 = 1).
  *  Enable transmission (TXEN0 = 1).
  *  Set 8-bit character mode (UCSZ00, UCSZ01, and UCSZ02 together control this,
  *  But UCSZ00, UCSZ01 are in Register UCSR0C). */
  sbi(UCSR1B, RXCIE1);
  cbi(UCSR1B, TXCIE1);
  cbi(UCSR1B, UDRIE1);
  sbi(UCSR1B, RXEN1);
  sbi(UCSR1B, TXEN1);
  cbi(UCSR1B, UCSZ12);
  
  /* USART Mode select -- UMSEL00 = 0 and UMSEL01 = 0 for asynchronous mode.
  *  disable parity mode -- UPM00 = 0 and UPM01 = 0.
  *  Set USBS = 1 to configure to 2 stop bits per DMX standard.  The USART receiver ignores this
  *  setting anyway, and will only set a frame error flag if the first stop bit is 0.  
  *  But, we have to set it to something.
  *  Finish configuring for 8 data bits by setting UCSZ00 and UCSZ01 to 1.  
  *  Set clock parity to 0 for asynchronous mode (UCPOL0 = 0). */
  cbi(UCSR1C, UMSEL10);
  cbi(UCSR1C, UMSEL11);
  cbi(UCSR1C, UPM10);
  cbi(UCSR1C, UPM11);
  sbi(UCSR1C, USBS1);
  sbi(UCSR1C, UCSZ10);
  sbi(UCSR1C, UCSZ11);
  cbi(UCSR1C, UCPOL1);
  
  
  UBRR1L = baudprescale; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
  UBRR1H = (baudprescale >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register

  sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
  
}





/** Setups the USART0 to communicate with a PC 
 *  \param baud the baudrate for communication */
void ArdSynthComm::setupUSB(unsigned long baud)
{
  /* The baud prescale that will be loaded into the
*  UBRR0H and UBRR0L registers to set the USART baud rate */
  unsigned long baudprescale;    
  baudprescale = (((clockspeed / (baud * 16UL))) - 1); //

  cli();  //disable interrupts while initializing the USART
  
  
  /* set transfer complete flag (TXC0 = 1).
  *  clear Frame Error flag (FE0 = 0).  
  *  clear Data overrun flag (DOR0 = 0).
  *  clear Parity overrun flag (UPE0 = 0).
  *  disable doubling of USART transmission speed (U2X0 = 0).  
  *  Disable Multi-Processor Communication Mode-- whatever that is. (MCPM0 = 0)  */
  sbi(UCSR0A, TXC0);
  cbi(UCSR0A, FE0);
  cbi(UCSR0A, DOR0);
  cbi(UCSR0A, UPE0);
  cbi(UCSR0A, U2X0); 
  cbi(UCSR0A, MPCM0);
  

  /* Enable Receive Interrupt (RXCIE0 = 1).
  *  Disable Tranmission Interrupt (TXCIE = 0).
  *  Disable Data Register Empty interrupt (UDRIE0 = 0).
  *  Enable reception (RXEN0 = 1).
  *  Enable transmission (TXEN0 = 1).
  *  Set 8-bit character mode (UCSZ00, UCSZ01, and UCSZ02 together control this,
  *  But UCSZ00, UCSZ01 are in Register UCSR0C). */
  sbi(UCSR0B, RXCIE0);
  cbi(UCSR0B, TXCIE0);
  cbi(UCSR0B, UDRIE0);
  sbi(UCSR0B, RXEN0);
  sbi(UCSR0B, TXEN0);
  cbi(UCSR0B, UCSZ02);
  
  /* USART Mode select -- UMSEL00 = 0 and UMSEL01 = 0 for asynchronous mode.
  *  disable parity mode -- UPM00 = 0 and UPM01 = 0.
  *  Set USBS = 1 to configure to 2 stop bits per DMX standard.  The USART receiver ignores this
  *  setting anyway, and will only set a frame error flag if the first stop bit is 0.  
  *  But, we have to set it to something.
  *  Finish configuring for 8 data bits by setting UCSZ00 and UCSZ01 to 1.  
  *  Set clock parity to 0 for asynchronous mode (UCPOL0 = 0). */
  cbi(UCSR0C, UMSEL00);
  cbi(UCSR0C, UMSEL01);
  cbi(UCSR0C, UPM00);
  cbi(UCSR0C, UPM01);
  sbi(UCSR0C, USBS0);
  sbi(UCSR0C, UCSZ00);
  sbi(UCSR0C, UCSZ01);
  cbi(UCSR0C, UCPOL0);
  
  
  UBRR0L = baudprescale; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
  UBRR0H = (baudprescale >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register

  sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

