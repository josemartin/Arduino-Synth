/*
  ArdSynthComm.h - Library used to configure low level settings of the Arduino Synth communications
  Setups the MIDI port communication using UART1 and USB communication using UART0 (builtin AtMega8U2).
  For use with Arduino Mega (AtMega 2560 or equivalent)
  
  Uses code form user ohnoezitasploded from Arduino official forums.
  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1236223363
  
  Version 1.0 April 24th, 2012
  J. Martin, S. Lopez
*/

#ifndef ArdSynthComm_h
#define ArdSynthComm_h

#include<Arduino.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
/* Definitions for setting and clearing register bits
*  See http://www.sigterm.de/projects/sens-o-nuts/Dokumentation/atmel/libc/group__avr__sfr.html */

/** MIDI standard baud rate */
#define MIDIbaudRate 31250




class ArdSynthComm
{
  public:
    void setupMIDI();
    void setupUSB(unsigned long int baud);
};

#endif

