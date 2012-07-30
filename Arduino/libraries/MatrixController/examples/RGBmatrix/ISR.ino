/** It's 0 if there is no multiplex operation taking place currently, and different if yes.
    If everything's fine, it shouldn't be neccesary...
    */
volatile uint8_t isShifting;

/** Stores the actual row that is being excitated in the RGB display.
    */
uint8_t shiftRow;


/** Excitates the desired row. The power stage is active low.
    \param row, The index of the row that should be activated. */
inline void setRow(int row) {
  PORTC = row;
}


/** Interrupt subrutine for Timer1, called after each PWM cycle.
    It switchs the row and shifts the new colour data.
    */
ISR(TIMER1_OVF_vect)
{
  if (!isShifting++) {
    
    digitalWrite(BLANK, HIGH);  // turn off the outputs. It's the first thing to avoid row interference.
    
    __asm__("nop\n\t");  // small delay after sending the data before transfering it to the registers.
    
    // set the registers
    digitalWrite(XLAT, HIGH);              
    __asm__("nop\n\t");       
    digitalWrite(XLAT, LOW);  
    
    __asm__("nop\n\t");  // delay before turning on the outputs
    
    setRow(shiftRow);          // set the new row

    digitalWrite(BLANK, LOW);      // turn on the outputs
      
    if (++shiftRow == NUM_ROWS){  // update the row variable
      shiftRow = 0;
    }
    
    matrix.shiftRowData(shiftRow);  // shifts the data of the next row, it only will take place in the following row change
    isShifting = 0;
  }
}




