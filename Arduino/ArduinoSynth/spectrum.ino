uint8_t spectrum_fadeSpectrumIndex[8][8];
#define SPECTRUM_MAX_SPECTRUM_FADE_INDEX 12
#define SPECTRUM_REFRESH_TIME_MS 20

/** Function to be continously called, handles the new data when needed and then, updates the matrix*/
void spectrumLoop() {
  if(millis() > time + SPECTRUM_REFRESH_TIME_MS) 
  {
    //Update the time variable
    time=millis();
    for (uint8_t i=0;i<NUM_ROWS;i++) 
    {         
      for(uint8_t j=0;j<NUM_COLS;j++)
      {
          if(spectrum_fadeSpectrumIndex[i][j]>0)
          {
            uint16_t colorF[3];
            colorF[0]=((matrix.getPixelR(i,j)*14)/15);
            colorF[1]=((matrix.getPixelG(i,j)*14)/15);
            colorF[2]=((matrix.getPixelB(i,j)*14)/15);
            
            matrix.setPixel(i,j, colorF[0], colorF[1], colorF[2]);
            spectrum_fadeSpectrumIndex[i][j]--;
            
          }
          else
          {
            matrix.setPixel(i,j,0,0,0);
          }
      }
    }
  }
  
  
  if (rxFlag == 1) {

    rxFlag=0; 
    
    
    for (uint8_t i=0;i<NUM_ROWS;i++) 
    {         
      for(uint8_t j=0;j<NUM_COLS;j++)
      {
        
        uint8_t ref=j*10;
        //Checks if the pixel needs to be painted
        if(rxData[0][i]>ref)
        { 
          spectrum_fadeSpectrumIndex[i][j]=SPECTRUM_MAX_SPECTRUM_FADE_INDEX;
          uint16_t refcol;
          switch (j) {
            case 0:
              refcol=1;
              break;
            case 1:
              refcol=5;
              break;
            case 2:
              refcol=9;
              break;
            case 3:
              refcol=10;
              break;
            case 4:
              refcol=11;
              break;
            case 5:
              refcol=13;
              break;
            case 6:
              refcol=14;
              break;
           case 7:
              refcol=17;
              break;
          }
          
          
          //Gets the color to be painted and paints it
          if (refcol>0 && (refcol)<9) // Blue-Green mix
          {
            matrix.setPixel(i,j,0, ((refcol)-1)*COLOUR17_SCALE_MULTIPLIER , (9 - (refcol))*COLOUR17_SCALE_MULTIPLIER);
          } 
          else 
          {
            if((refcol)>8 && (refcol)<18)  // Green-Red mix
            {
              matrix.setPixel(i,j, ((refcol)-9)*COLOUR17_SCALE_MULTIPLIER, (17 - (refcol))*COLOUR17_SCALE_MULTIPLIER,0);              
            }
          }
        }
       
      }
    }
  } 
}
