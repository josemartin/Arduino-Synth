/**
  MatrixController.h - Collection of functions to control a RGB LED matrix.

  J. Martin, S. Lopez
*/



#include <Arduino.h>
#include "MatrixController.h"
#include "Tlc5940Mux.h"


/** Creates the MatrixController instance. */
MatrixController::MatrixController()
{
}


/** Initializes the matrix (TlcMux_init). 
    \param initialValue, value to initalize al channels in TlcMux library.
    It results in a grade of white.    
    */
void MatrixController::init(uint8_t initialValue)
{
  TlcMux_init(initialValue);
}


/** Shifts a row RGB data through SPI (TlcMux_shiftRow).
    Used in ISR to change the row.  
    \param row, row to set.  
    */
void MatrixController::shiftRowData(uint8_t row) 
{
  TlcMux_shiftRow(row);  // shift the new data
}


/** Sets a single pixel's RGB data
    \param row, row of the pixel
    \param col, column of the pixel
    \param r, red part of the color (0-4095)
    \param g, green part of the color (0-4095)
    \param b, blue part of the color (0-4095)

    */
void MatrixController::setPixel(int row, int col,int r, int g, int b) {
  TlcMux_set(row, col,r);
  TlcMux_set(row, col+16,g);
  TlcMux_set(row, col+8,b);
}


/** Sets a row's RGB data
    \param row, row to paint
    \param r, red part of the color (0-4095)
    \param g, green part of the color (0-4095)
    \param b, blue part of the color (0-4095)
    */
void MatrixController::setRow(int row , int r, int g, int b) {
  for (uint8_t col = 0; col < 8; col++) {
    setPixel(row, col, r, g, b);
  }
}


/** Sets a column's RGB data
    \param col, column to paint
    \param r, red part of the color (0-4095)
    \param g, green part of the color (0-4095)
    \param b, blue part of the color (0-4095)

    */
void MatrixController::setCol(int col , int r, int g, int b) {
  for (uint8_t row = 0; row < 8; row++) {
    setPixel(row, col, r, g, b);
  }
}


/** Sets a matrix's RGB data
    \param r, red part of the color (0-4095)
    \param g, green part of the color (0-4095)
    \param b, blue part of the color (0-4095)
    */
void MatrixController::setMatrix(int r, int g, int b) {  
  for (uint8_t row = 0; row < NUM_ROWS; row++) {
    for (int pix= 0; pix<8;pix++) {
      setPixel(row, pix, r, g, b);
      
    }
  }
}


/** Returns a pixel's red value.
    \return red value (0-4095).
    */
uint16_t MatrixController::getPixelR(int row, int num) {
  return TlcMux_get(row, num);
}

/** Returns a pixel's green value.
    \return green value (0-4095).
    */
uint16_t MatrixController::getPixelG(int row, int num) {
  return TlcMux_get(row, num+16);
}

/** Returns a pixel's blue value.
    \return blue value (0-4095).
    */
uint16_t MatrixController::getPixelB(int row, int num) {
  return TlcMux_get(row, num+8);
}

/** Shifts the pixels in a row. Px 0 will be 1, etc.
    Pixel 7 color value is discarded.
    \param row, row to shift
    */
void MatrixController::shiftFila (int row) {
  setPixel(row, 7, getPixelR(row,6),getPixelG(row,6),getPixelB(row,6));
  setPixel(row, 6, getPixelR(row,5),getPixelG(row,5),getPixelB(row,5));
  setPixel(row, 5, getPixelR(row,4),getPixelG(row,4),getPixelB(row,4));
  setPixel(row, 4, getPixelR(row,3),getPixelG(row,3),getPixelB(row,3));
  setPixel(row, 3, getPixelR(row,2),getPixelG(row,2),getPixelB(row,2));
  setPixel(row, 2, getPixelR(row,1),getPixelG(row,1),getPixelB(row,1));
  setPixel(row, 1, getPixelR(row,0),getPixelG(row,0),getPixelB(row,0));
}
