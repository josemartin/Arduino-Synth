#define POPVIS_FADE_STEPS 250

/** Variables to store the actual color on each point of the matrix and theirs states */
static uint8_t popvis_pxData[8][8][2];
static uint16_t popvis_pxColors[8][8][3];
static uint8_t popvis_filledDots;

/** Visualization initialization */
void PopVisualization()
{
  for (uint8_t i=0;i<NUM_ROWS;i++)
  {
    for (uint8_t j=0;j<NUM_COLS;j++)
    {
      popvis_pxData[i][j][0]=0;
      popvis_pxColors[i][j][0]=0;
      popvis_pxColors[i][j][1]=0;
      popvis_pxColors[i][j][2]=0;
      popvis_filledDots=0;
    }
  }
}

/** Perform a fade of all points in the matrix */
void nextStep()
{
  for (uint8_t i=0;i<8;i++)
  {
    for (uint8_t j=0;j<8;j++)
    {
      /* We first check for the descending fade because we can pass from ascending to descending, but no otherwise, so no need to do anitated if */
      if(popvis_pxData[i][j][1]==2)
      {
        //Color calculation
        uint16_t color[3];
        color[0]=((popvis_pxColors[i][j][0]/POPVIS_FADE_STEPS)*(popvis_pxData[i][j][0]));
        color[1]=((popvis_pxColors[i][j][1]/POPVIS_FADE_STEPS)*(popvis_pxData[i][j][0]));
        color[2]=((popvis_pxColors[i][j][2]/POPVIS_FADE_STEPS)*(popvis_pxData[i][j][0]));
        matrix.setPixel(i,j,color[0],color[1],color[2]);
        
        if(popvis_pxData[i][j][0]>0) // We check if we haven't turned off yet the pixel
        {
          popvis_pxData[i][j][0]--;
        }
        else // That means we turned off the pixel, so it position is now free
        {
          popvis_pxData[i][j][1]=0; // Turn off operation in this pixel
          popvis_filledDots--;       // Decrement the filledDots
        }   
      }
      else { 
        if(popvis_pxData[i][j][1]==1)
        {
         //Color calculation
          uint16_t color[3];
          color[0]=((popvis_pxColors[i][j][0]/POPVIS_FADE_STEPS)*(popvis_pxData[i][j][0]));
          color[1]=((popvis_pxColors[i][j][1]/POPVIS_FADE_STEPS)*(popvis_pxData[i][j][0]));
          color[2]=((popvis_pxColors[i][j][2]/POPVIS_FADE_STEPS)*(popvis_pxData[i][j][0]));
          matrix.setPixel(i,j,color[0],color[1],color[2]);
     
          if(popvis_pxData[i][j][0]<POPVIS_FADE_STEPS) // We check if we haven't reached the maximum brightness
          {
            popvis_pxData[i][j][0]++;
          }
          else // If it's reached, we turn to fade out mode
          {
            popvis_pxData[i][j][0]--;
            popvis_pxData[i][j][1]=2;
          }   
        }
        else
        {
          matrix.setPixel(i,j,0,0,0);
        }
      }
      
    }
  }
}

/** Adds a new point in the matrix */
uint8_t newItem(uint8_t level) 
{
  uint8_t trys=0;
    while (trys<30) 
    {
      trys++;
      // Pick a random position to paint
      uint8_t tryx=random(8);
      uint8_t tryy=random(8);
      
      // Check if the position is free
      if(popvis_pxData[tryx][tryy][0]==0) 
      {
        // Set up the position
        popvis_filledDots++;
        setDot(level, tryx, tryy);
        return true;
      }
    }
  
  return false;
}


/** Sets a new point with the desired color in the range */
void setDot(uint8_t level, uint8_t posX, uint8_t posY)
{
  // Pick the color 1-18 and set up the pixel
  if (level>0 && level<9) // Blue-Green mix
  {
    popvis_pxColors[posX][posY][0]=0;
    popvis_pxColors[posX][posY][1]=(level - 1) * COLOUR17_SCALE_MULTIPLIER;
    popvis_pxColors[posX][posY][2]=(9 - level) * COLOUR17_SCALE_MULTIPLIER;
    popvis_pxData[posX][posY][0]=POPVIS_FADE_STEPS/2;
    popvis_pxData[posX][posY][1]=1;
  } 
  else 
  {
    if(level>8 && level<18)  // Green-Red mix
    {
      popvis_pxColors[posX][posY][2]=0;
      popvis_pxColors[posX][posY][0]=(level - 9) * COLOUR17_SCALE_MULTIPLIER;
      popvis_pxColors[posX][posY][1]=(17 - level) * COLOUR17_SCALE_MULTIPLIER;
      popvis_pxData[posX][posY][0]=POPVIS_FADE_STEPS/2;
      popvis_pxData[posX][posY][1]=2;
    }
  }
  
}


/** Function to be continously called, handles the refresh and the new data */
void popVisLoop () {
  if (millis() > time + 100  || millis()<time) {
    popvis_acumulador+=popvis_contador;
    popvis_contaMedia++;
    if (popvis_contaMedia==30)
    {
      popvis_baremo=popvis_acumulador/popvis_contaMedia;
      if (popvis_baremo<3) popvis_baremo=3;
      
      popvis_contaMedia=0;
      popvis_acumulador=0;
    }
    
    time=millis();

    int touse=(popvis_contador*95/popvis_baremo)/10;
    
    
    if (touse>17) touse = 17;

    for (int i=0;i<touse/2;i++)
    {
      newItem(touse);
    }
    popvis_contador=0;
  }
  
  nextStep();
  delayMicroseconds(300);
}
