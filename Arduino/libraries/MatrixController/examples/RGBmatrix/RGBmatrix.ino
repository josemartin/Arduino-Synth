/**
    RGB matrix controller example.using MatrixController library and Tlc5940Mux.
    
    28-04-2012
    Jose Martin
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
#define  NUM_COL 8

/** Defines the correction cycles to add to the Timer1 due to the processing time of the row change */
#define TLC_CORRECTION_CYCLES 160

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

/** Matrix controller library */
#include <MatrixController.h>

/** MatrixController instance */
MatrixController matrix;




/** System initialization routine*/
void setup()
{
  /* Defining the pin modes for XLAT and BLANK*/
  pinMode(XLAT,OUTPUT);
  pinMode(BLANK, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(8, LOW);
  
  
  
  // For Arduino Duemilanove/Uno, etc. Using the analog port (PORTC) to drive the row, analog 0-2 to a 3 to 8 decoder.  
  DDRC |= _BV(PC0) | _BV(PC1) | _BV(PC2); //Configure analog inputs as digital
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  //End of the Arduino Duemilanove/Uno stuff
  
  
  
  //If using Arduino Mega, comment the previous section and uncomment this.
  //For Arduino Mega, use the pinMode 35-37. Output 37 is LSB, output 35 is MSB of the 3 to 8 decoder
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  
  
  
  
  
  /* Matrix initialization */
  matrix.init(0);



  
  /* Startup line draw and check.*/
  startupAnimation();
}



void loop()
{
  
  
}


/** Draws the columns in a different colour and draws a check 
    See the Graph tab to see what it does 
    */
void startupAnimation() {
  initialDraw ();
  delay(1000);
  matrix.setMatrix(0,0,0);
  drawCheck();
}


