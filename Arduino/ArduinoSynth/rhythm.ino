/** Define constants used to calculate colors and color intensities */
#define RHYTHM_MAX_NOTE 18
#define RHYTHM_MAX_INT 16
#define RHYTHM_MAX_INT_1 16

/**Constants with the thresholds to calculate the mask to be applied */
#define RHYTHM_CH1_THRESHOLD1 4
#define RHYTHM_CH1_THRESHOLD2 10
#define RHYTHM_CH1_THRESHOLD3 14
#define RHYTHM_CH2_THRESHOLD1 7
#define RHYTHM_CH2_THRESHOLD2 9
#define RHYTHM_CH2_THRESHOLD3 10
#define RHYTHM_CH3_THRESHOLD 8

/** Refresh period */
#define RHYTHM_REFRESH_TIME_MS 50

/** Off interval when a new note is received if the previous one is still in screen */
#define RHYTHM_offDelay 20



//Mask to write the channel 1
const uint8_t rhythm_pxtoWrite1 [4][8][8] = {{{0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0}},
                                   
                                   {{0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,1,1,1,1,0,0},
                                   {0,0,1,1,1,1,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0}},
                                   
                                   {{0,0,0,0,0,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,1,1,1,1,1,1,0},
                                   {0,1,1,1,1,1,1,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,0,0,0,0,0}},
                                   
                                   {{0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {1,1,1,1,1,1,1,1},
                                   {1,1,1,1,1,1,1,1},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0},
                                   {0,0,0,1,1,0,0,0}}};
//Masks to write the channel 2, one for each level
const uint8_t rhythm_pxtoWrite2 [5][8][8]={{{0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,1,0,0,1,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,1,0,0,1,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0}},
                                                                      
                                   {{0,0,0,0,0,0,0,0},
                                   {0,1,1,0,0,1,1,0},
                                   {0,1,1,0,0,1,1,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,1,1,0,0,1,1,0},
                                   {0,1,1,0,0,1,1,0},
                                   {0,0,0,0,0,0,0,0}},
                                   
                                   {{0,1,0,0,0,0,1,0},
                                   {1,1,1,0,0,1,1,1},
                                   {0,1,1,0,0,1,1,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,1,1,0,0,1,1,0},
                                   {1,1,1,0,0,1,1,1},
                                   {0,1,0,0,0,0,1,0}},
                                   
                                   {{1,1,0,0,0,0,1,1},
                                   {1,1,1,0,0,1,1,1},
                                   {0,1,1,0,0,1,1,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,1,1,0,0,1,1,0},
                                   {1,1,1,0,0,1,1,1},
                                   {1,1,0,0,0,0,1,1}}};                                
                                   

/** Stores the colours present in the visualizations */
uint16_t rhythm_ch0[4];
uint16_t rhythm_rhythmData[8][8][5];


/** Draws the visualizations using the actual visualization data */
void rhythmDraw () {
  uint16_t graphBuffer[8][8][3];
  
  //Initialize the matrix turned off
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      graphBuffer[i][j][0]=0;
      graphBuffer[i][j][1]=0;
      graphBuffer[i][j][2]=0;
    }
  }
  
  
  //Draw the background
  if (rhythm_ch0[3]>0)
  {
    uint16_t newColor[3];
    
    //Create the background color
    uint16_t scale = (RHYTHM_MAX_INT + 1 - rhythm_ch0[3]) * (RHYTHM_MAX_INT + 1 - rhythm_ch0[3])  *5;
    newColor[0]=rhythm_ch0[0] / scale;
    newColor[1]=rhythm_ch0[1] / scale;
    newColor[2]=rhythm_ch0[2] / scale;
    
    //Draw the background
    for (uint8_t i=0;i<NUM_ROWS;i++)
    {
      for (uint8_t j=0;j<NUM_COLS;j++)
      {
        graphBuffer[i][j][0]=newColor[0];
        graphBuffer[i][j][1]=newColor[1];
        graphBuffer[i][j][2]=newColor[2];
      }
    }
  }
  
  
  
  //Update the fade out of the rest sectors
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      if(rhythm_rhythmData[i][j][3]>0)
      {
        uint16_t newColor[3];
        
        //Create the new color
        newColor[0]=(rhythm_rhythmData[i][j][0] / RHYTHM_MAX_INT_1) * rhythm_rhythmData[i][j][3];
        newColor[1]=(rhythm_rhythmData[i][j][1] / RHYTHM_MAX_INT_1) * rhythm_rhythmData[i][j][3];
        newColor[2]=(rhythm_rhythmData[i][j][2] / RHYTHM_MAX_INT_1) * rhythm_rhythmData[i][j][3];
        
        //Draw the pixel
        graphBuffer[i][j][0]=newColor[0];
        graphBuffer[i][j][1]=newColor[1];
        graphBuffer[i][j][2]=newColor[2];
      }
      
      //If there was a pending new color (maybe not used in the visualization), write it for the next draw.
      if(rhythm_rhythmData[i][j][4]>0)
      {
        rhythm_rhythmData[i][j][3]=rhythm_rhythmData[i][j][4];
        rhythm_rhythmData[i][j][4]=0;
      }  
    }
  }
    

  //Draw the matrix with the calculated pixels
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      matrix.setPixel(i,j, graphBuffer[i][j][0],graphBuffer[i][j][1],graphBuffer[i][j][2]);
    }
  }
  
}


/** Performs a refresh of the visualization, fading the needed colors */
void rhythmFadeAndDraw () {
  
  //Fade a step of the pixels and background
  if(rhythm_ch0[3]>0) 
  {
    rhythm_ch0[3]--;
  }
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      if(rhythm_rhythmData[i][j][3] > 0)
      {
        rhythm_rhythmData[i][j][3]--;
      }
    }
  } 
  
  
  //Draw the frame
  rhythmDraw();
}



/** Function to be continously called, handles the refresh and the new data when needed */
void rhythmLoop() {
  
  //Check if it's time to refresh the matrix
  if(millis() > time + RHYTHM_REFRESH_TIME_MS) 
  {
    //Update the time variable
    time=millis();
    
    rhythmFadeAndDraw ();
  }
          

  //Check if there's new data received from PC
  if(rxFlag>0) {
    
    rhythmProcessData();
  }
}
    
    
/** Handles the new data from the PC and draws it to the visualization */
void rhythmProcessData() {
    
    //Check which section has to be painted
    switch(rxFlag)
    {
      case 1:
        rxFlag=0; //Discard energy frames
        break;
        
      //Paint the background
      case 2:
        rxFlag=0;
        
        rhythmSetCh0();
        break; 
        
      //Paint the central square  
      case 3:
        rxFlag=0;
      
        rhythmSetCh1();
        break;
        
      //Paint the corners  
      case 4:
        rxFlag=0;
        
        rhythmSetCh2();
        break;
        
      //Paint the four squares  
      case 5:
        rxFlag=0;
        
        //rhythmSetCh3();
        break;
    }
 
}


/** Paints the new data of the background */
void rhythmSetCh0() {
  uint8_t refcol, refint;
  uint16_t newColor[3]={0,0,0};
  uint8_t offFlag=0;
        
  //Get the colour tone and paint it
  refcol = rxData[1][0];
  refint = rxData[1][1];
  if (refcol>0 && (refcol)<9) // Blue-Green mix
  {
    rhythm_ch0[0]=0;
    rhythm_ch0[1]=((refcol)-1)*COLOUR17_SCALE_MULTIPLIER;
    rhythm_ch0[2]=(9 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
    rhythm_ch0[3]=refint;
  } 
  else 
  {
    if((refcol)>8 && (refcol)<18)  // Green-Red mix
    {
      rhythm_ch0[0]=((refcol)-9)*COLOUR17_SCALE_MULTIPLIER;
      rhythm_ch0[1]=(17 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
      rhythm_ch0[2]=0;
      rhythm_ch0[3]=refint;            
    }
  }
  //Repaint
  rhythmDraw();
}



/** Paints the new data of the channel 1 */
void rhythmSetCh1() {
  uint8_t refcol, refint;
  uint16_t newColor[3]={0,0,0};
  uint8_t offFlag=0;
        
        
                                       
  //Get the colour tone and set the color
  refcol = rxData[2][0];   
  refint = rxData[2][1];
  if (refcol>0 && (refcol)<9) // Blue-Green mix
  {
                                          
    newColor[0]=0;
    newColor[1]=((refcol)-1)*COLOUR17_SCALE_MULTIPLIER;
    newColor[2]=(9 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
    
  } 
  else 
  {
    if((refcol)>8 && (refcol)<18)  // Green-Red mix
    {
      
      newColor[0]=((refcol)-9)*COLOUR17_SCALE_MULTIPLIER;
      newColor[1]=(17 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
      newColor[2]=0;
    }
  }
  
  //Set the mask to use
  uint8_t mask;
  if(refint < RHYTHM_CH1_THRESHOLD1)
  {
    mask=0;
  }
  else
  {
    if (refint<RHYTHM_CH1_THRESHOLD2)
    {
      mask=1;
    }
    else
    {
      if (refint<RHYTHM_CH1_THRESHOLD3)
      {
        mask=2;
      }
      else
      {
        mask=3;
      }
    }
  }
  
  //Set the pixels with that color  
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      if (rhythm_pxtoWrite1[mask][i][j]==1)
      {
        if (rhythm_rhythmData[i][j][3]>0)
        {
          rhythm_rhythmData[i][j][3]=0;
          offFlag=1;
        }
        else
        {
          rhythm_rhythmData[i][j][3]=refint;
        }
        rhythm_rhythmData[i][j][0]=newColor[0];
        rhythm_rhythmData[i][j][1]=newColor[1];
        rhythm_rhythmData[i][j][2]=newColor[2];             
      } 
    }
  }
  
  //Repaint
  rhythmDraw();
  
  //If the was data from this channel in the visualization, we turn it off and later, we paint the new
  if (offFlag)
  {
    delay(30);
    for (uint8_t i=0;i<NUM_ROWS;i++)
    {
      for (uint8_t j=0;j<NUM_COLS;j++)
      {
        if (rhythm_pxtoWrite1[mask][i][j]==1)
        {          
            rhythm_rhythmData[i][j][3]=refint;          
        } 
      }
    }
    rhythmDraw();
  }
}
  
  
/** Paints the new data of the channel 2 */  
void rhythmSetCh2 () 
{
  uint8_t refcol, refint;
  uint16_t newColor[3]={0,0,0};
  uint8_t offFlag=0;
  
  //Get the colour tone and set the color
  refcol = rxData[3][0];   
  refint = rxData[3][1];
  if (refcol>0 && (refcol)<9) // Blue-Green mix
  {
                                          
    newColor[0]=0;
    newColor[1]=((refcol)-1)*COLOUR17_SCALE_MULTIPLIER;
    newColor[2]=(9 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
    
  } 
  else 
  {
    if((refcol)>8 && (refcol)<18)  // Green-Red mix
    {
      
      newColor[0]=((refcol)-9)*COLOUR17_SCALE_MULTIPLIER;
      newColor[1]=(17 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
      newColor[2]=0;
    }
  }
  
  //Set the mask to use
  uint8_t mask;
  if(refint < RHYTHM_CH2_THRESHOLD1)
  {
    mask=0;
  }
  else
  {
    if (refint<RHYTHM_CH2_THRESHOLD2)
    {
      mask=1;
    }
    else
    {
      if (refint<RHYTHM_CH2_THRESHOLD3)
      {
        mask=2;
      }
      else
      {
        mask=3;
      }
    }
  }
      
  
  
  
  
  
  //Set the pixels with that color
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      if (rhythm_pxtoWrite2[mask][i][j]==1)
      {
        if (rhythm_rhythmData[i][j][3]>0 )   //&& rhythm_rhythmData[i][j][3]<7
        {
          rhythm_rhythmData[i][j][3]=0;
          offFlag=1;
        }
        else
        {
          rhythm_rhythmData[i][j][3]=refint;
        }
        rhythm_rhythmData[i][j][0]=newColor[0];
        rhythm_rhythmData[i][j][1]=newColor[1];
        rhythm_rhythmData[i][j][2]=newColor[2];             
      } 
    }
  }
  
  //Repaint
  rhythmDraw();
  
  //If the was data from this channel in the visualization, we turn it off and later, we paint the new
  if (offFlag)
  {
    delay(30);
    for (uint8_t i=0;i<NUM_ROWS;i++)
    {
      for (uint8_t j=0;j<NUM_COLS;j++)
      {
        if (rhythm_pxtoWrite2[mask][i][j]==1)
        {          
            rhythm_rhythmData[i][j][3]=refint;
        } 
      }
    }
    rhythmDraw();
  }
}


/** Paints the new data of the channel 3 */
/*void rhythmSetCh3 ()
{
  uint8_t refcol, refint;
  uint16_t newColor[3]={0,0,0};
  uint8_t offFlag=0;
  //Get the colour tone and set the color
  refcol = rxData[4][0];   
  refint = rxData[4][1];
  if (refcol>0 && (refcol)<9) // Blue-Green mix
  {
                                          
    newColor[0]=0;
    newColor[1]=((refcol)-1)*COLOUR17_SCALE_MULTIPLIER;
    newColor[2]=(9 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
    
  } 
  else 
  {
    if((refcol)>8 && (refcol)<18)  // Green-Red mix
    {
      
      newColor[0]=((refcol)-9)*COLOUR17_SCALE_MULTIPLIER;
      newColor[1]=(17 - (refcol))*COLOUR17_SCALE_MULTIPLIER;
      newColor[2]=0;
    }
  }
  
  //Set the mask to use
  uint8_t mask;
  if(refint<RHYTHM_CH3_THRESHOLD)
  {
    mask=0;
  }
  else
  {
    mask=1;
  }
  
  //Set the pixels with that color
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      if (rhythm_pxtoWrite3[mask][i][j]==1)
      {
        if (rhythm_rhythmData[i][j][3]>0)
        {
          rhythm_rhythmData[i][j][3]=0;
          offFlag=1;
        }
        else
        {
          rhythm_rhythmData[i][j][3]=refint;
        }
        rhythm_rhythmData[i][j][0]=newColor[0];
        rhythm_rhythmData[i][j][1]=newColor[1];
        rhythm_rhythmData[i][j][2]=newColor[2];             
      } 
    }
  }
  
  //Repaint
  rhythmDraw();
  
  //If the was data from this channel in the visualization, we turn it off and later, we paint the new
  if (offFlag)
  {
    delay(30);
    for (uint8_t i=0;i<NUM_ROWS;i++)
    {
      for (uint8_t j=0;j<NUM_COLS;j++)
      {
        if (rhythm_pxtoWrite3[mask][i][j]==1)
        {          
            rhythm_rhythmData[i][j][3]=refint;          
        } 
      }
    }
    rhythmDraw();
  }
}*/
