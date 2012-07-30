/*
    Arduino Synth
 Provides an USB MIDI interface along with a visualization system commandable by a PC.
 
 
 Controls an RGB matrix multiplexed and controlled by two TLC5940 from TI.
 Uses TLC5940Mux_2 library with modified interrupt subrutine and timing corrections.
  
 J. Martin, S. Lopez
 Spring 2012
 */



/** Number of TLCs daisy-chained.  To daisy-chain, attach the SOUT (TLC pin 17)
    of the first TLC to the SIN (TLC pin 26) of the next.  The rest of the pins
    are attached normally.
    The first one haves Red0-7 in CH0-7 and Blue0-7 in CH8-15.
    The second one haves Green0-7 in CH0-7. The other 8 channels aren't connected.
    
    \note Each TLC needs it's own IREF resistor */
#define  NUM_TLCS  2

/** Number of rows of the LED matrix, it configures the buffer and the shift routine.*/
#define  NUM_ROWS  8

/** Number of columns of the LED matrix, just to use the number in loops.*/
#define  NUM_COLS 8
  
/** Defines the correction cycles to add to the Timer1 due to the processing time of the row change */
#define TLC_CORRECTION_CYCLES 170

/** BLANK signal pin for the TLC5940.
    \note There are problems when using PWM outputs in Arduino due timers/PWM interference.
    The best option is to use analog pins configured as digital outputs for that.
    */
    
#define BLANK 8

/** XLAT signal pin for the TLC5940.
    \note There are problems when using PWM outputs in Arduino due timers/PWM interference.
    The best option is to use analog pins configured as digital outputs for that.
    */
#define XLAT 2

/** Data rate for communications. */
#define USBrate 57600

 /** Main library.*/
//#include "Tlc5940Mux.h"


/** Communication library */
#include <ArdSynthComm.h>

/** LED Matrix library */
#include <MatrixController.h>

/** Matrix library instance */
MatrixController matrix;

/** nombrar o arreglar toas estas*/
//int colorsal[3],colorsal2[3];
int effects_color[3], effects_colorsal[3], effects_colorsal2[3];


uint8_t effects_nextRGBcolorState;

unsigned long time;

/** Variables for the pop visualization. They handle all the data related to the byte counter and the music feedback. */
volatile int popvis_contador;
uint16_t popvis_contaMedia, popvis_acumulador;
uint8_t popvis_baremo;

/** Active visualization */
uint8_t activeVis;




/** ArdSynthComm instace */
ArdSynthComm comm;

/** holds the incoming byte from the receive buffer. */
volatile byte ReceivedByte = 0; 




/** System initialization routine*/
void setup()
{
  /* Defining the pin modes and out for XLAT, BLANK and the LED status */
  pinMode(2,OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  digitalWrite(2, LOW);
  digitalWrite(8, LOW);
  
    /* For Arduino Mega, use the pinMode 35-37, for normal arduino, use xDDRC to use analog port as outputs and pinmoe on 14-16*/
  //xDDRC |= _BV(PC0) | _BV(PC1) | _BV(PC2); //Configure analog inputs as digital - not needed in mega2560, in mega use pnmode
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  
  /** Only for duemilanove
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);*/
  
  /* Initialize the serial connection with PC. 57600 bauds. */
  comm.setupUSB(USBrate); //Setup the USB interface
  comm.setupMIDI();
  
  
  /* Initialize hte matrix to black */
  matrix.init(0);
  
  
  /* Variable initializations for pop visualization */
  popvis_contador=0;
  popvis_contaMedia=0;
  popvis_acumulador=0;
  popvis_baremo=5;
  
  /* Start with the audiorhytm visualization */
  activeVis=0;
  
  /* Initialize the pseudorandom generator with a seed taken from an unconnected analog pin */
  randomSeed(analogRead(0));

  /* Variable initializations */
  effects_nextRGBcolorState=0;
  
  /* Visualization inicialization */
  PopVisualization();
  
  
  
  time=millis();
  
  
  /* Startup line draw and check. */
  startupAnimation();
  
  
  
  
}


  


void loop()
{
  //Calls the loop fuction of the visualization.
  switch(activeVis)
  {
    case 0:
    rhythmLoop();
    break;
    case 1:
    spectrumLoop();
    break;
    case 2:
    popVisLoop ();
    break;
    case 3:
    showCaseLoop ();
    break;
  }
}





