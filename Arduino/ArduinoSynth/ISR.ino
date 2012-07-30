/** It's 0 if there is no multiplex operation taking place currently, and different if yes.
    If everything's fine, it shouldn't be neccesary...
    */
volatile uint8_t isShifting;

/** Stores the actual row that is being excitated in the RGB display.
    */
uint8_t shiftRow;

/** Stores the last received data */
volatile uint8_t rxData[5][9];

/** Flags and state variables for managing the incoming data */
volatile uint8_t rxState; 
volatile uint8_t rxIndex; 
volatile uint8_t rxFlag;


/** Excitates the desired row. The power stage is active low.
    \param row, The index of the row that should be activated. */
inline void setRow(int row) {
  PORTA = row;
}

/** Interrupt subrutine for Timer1, called after each PWM cycle.
    It switchs the row and shifts the new colour data.
    */
ISR(TIMER1_OVF_vect)
{
  if (!isShifting++) {
    digitalWrite(BLANK, HIGH);  // turn off the outputs. It's the first thing to avoid row interlacing.
    
    // 3 x 62.5ns = 187.5ns  (Blank needs to exceed 300ns to avoid shortening the GS cycle)
    __asm__("nop\n\t""nop\n\t""nop\n\t");  // small delay after sending the data before transfering it to the registers
    
    digitalWrite(XLAT, HIGH);              // set the registers
    // XLAT for 62.5 ns
    __asm__("nop\n\t");       
    digitalWrite(XLAT, LOW);  
    
    // Another 187.5 ns safely exceeding the minimum 300ns BLANK requirement    
    __asm__("nop\n\t""nop\n\t""nop\n\t");  // delay after turning on the outputs
    
    setRow(shiftRow);          // set the new row

      digitalWrite(BLANK, LOW);      // turn on the outputs
      
    if (++shiftRow == NUM_ROWS){  // update the row variable
      shiftRow = 0;
    }
    
    matrix.shiftRowData(shiftRow);
    isShifting = 0;
  }
}



/** Interrupt subrutine of USART1 byte reception.
    It replicates the received byte from the MIDI port to the USB throught USART0
    */
ISR(USART1_RX_vect){
  uint8_t MIDIbyte = UDR1;  
  UDR0 = MIDIbyte;
} 





/** Interrupt subrutine of USART0 byte reception.
    It drives the received byte to the visualization system.
    */
ISR(USART0_RX_vect){
  popvis_contador++;
  
  ReceivedByte = UDR0;  
  
  
  //Checks if it's a command byte
  if (ReceivedByte >=200)
  {
    //Sets the actual incoming frame or sets the active visualization
    if(ReceivedByte<205)
    {
      rxState=ReceivedByte-200;
      rxIndex=0;
    }
    else
    {
      activeVis=ReceivedByte-205;
    }
  }
  else
  {
    //Saves the byte where it should be saved
    rxData[rxState][rxIndex]=ReceivedByte;
    rxIndex++;
    
    if (rxIndex>1)
    {
      if (rxIndex==9)
      {
        rxFlag=rxState + 1;
        rxIndex=0;
      }
      else
      {
        if (rxState > 0 && rxIndex == 2)
        {
          rxFlag=rxState + 1;
         
        }
      }
    }
   
  }
} 


