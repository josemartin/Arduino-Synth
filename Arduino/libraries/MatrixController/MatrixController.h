/*
  MatrixController.h - Collection of functions to control a RGB LED matrix.

  J. Martin, S. Lopez
*/

#ifndef MatrixController_h
#define MatrixController_h

#include "Arduino.h"
#include "Tlc5940Mux.h"


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

/** Number of rows of the LED matrix, it configures the buffer and the shift routine.*/
#define  NUM_ROWS  8

/** Number of columns of the LED matrix, just to use the number in loops.*/
#define  NUM_COL 8


class MatrixController
{
  public:
    MatrixController();
    
    void shiftRowData(uint8_t row);  
    
    void init(uint8_t initialValue);
    
    void setPixel(int row, int col,int r, int g, int b);
    void setRow(int row,int r, int g, int b);
    void setCol(int col,int r, int g, int b);
    void setMatrix(int r, int g, int b);
    
    uint16_t getPixelR(int row, int num);
    uint16_t getPixelG(int row, int num);
    uint16_t getPixelB(int row, int num);
    
    void shiftFila (int row);

  private:

};

#endif
