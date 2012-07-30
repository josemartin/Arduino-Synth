#define SHOWCASE_INTOOUT_DELAY 100
#define SHOWCASE_PULSE_DELAY 10
#define SHOWCASE_INTOOUT_STEP 400
#define SHOWCASE_SHIFTRGB_STEP 40
#define SHOWCASE_LIGHTPULSE_MAX 40
#define SHOWCASE_LIGHTPULSE_STEP 20

/** Demo visualization, not commanded */
void showCaseLoop() {
  lightPulse();
  effects_nextRGBcolorState=0;
  for (int i=0;i<1000;i++) {
    shiftRGBColors();
  }
  flickerTest();
  
  effects_nextRGBcolorState=0;
  for (int i=0;i<50;i++) {
    inToOutEffect();
  }
}



/* Performs a pulse in the entire matrix with the required color */
void pulseRGB (int p, int r, int g, int b) {
  int pr=r / p;
  int pg=g / p;
  int pb=b/ p;
  matrix.setMatrix(0,0,0);
  for (int i=1;i<=p;i++) {
    matrix.setMatrix(i*pr,i*pg,i*pb);
    delay(SHOWCASE_PULSE_DELAY);
  }
  for (int i=p;i>=0;i--) {
    matrix.setMatrix(i*pr,i*pg,i*pb);
    delay(SHOWCASE_PULSE_DELAY);
  }
}


/** Performs and in to out effect step */
void inToOutEffect() {
  nextRGBColor(SHOWCASE_INTOOUT_STEP);
  
  inToOut();
  delay(SHOWCASE_INTOOUT_DELAY);
}


/** Shifts the pixels in a row. Px 0 will be 1, etc.
    Pixel 7 color value is stored in effects_colorsal. It's similar to the one included in the MatrixController
    \param row, row to shift
    */
void shiftFilaShift (int row) {
  effects_colorsal[0]=matrix.getPixelR(row,7);
  effects_colorsal[1]=matrix.getPixelG(row,7);
  effects_colorsal[2]=matrix.getPixelB(row,7);
  matrix.setPixel(row, 7, matrix.getPixelR(row,6),matrix.getPixelG(row,6),matrix.getPixelB(row,6));
  matrix.setPixel(row, 6, matrix.getPixelR(row,5),matrix.getPixelG(row,5),matrix.getPixelB(row,5));
  matrix.setPixel(row, 5, matrix.getPixelR(row,4),matrix.getPixelG(row,4),matrix.getPixelB(row,4));
  matrix.setPixel(row, 4, matrix.getPixelR(row,3),matrix.getPixelG(row,3),matrix.getPixelB(row,3));
  matrix.setPixel(row, 3, matrix.getPixelR(row,2),matrix.getPixelG(row,2),matrix.getPixelB(row,2));
  matrix.setPixel(row, 2, matrix.getPixelR(row,1),matrix.getPixelG(row,1),matrix.getPixelB(row,1));
  matrix.setPixel(row, 1, matrix.getPixelR(row,0),matrix.getPixelG(row,0),matrix.getPixelB(row,0));
}


/** Fills alternatively the matrix with the three primary colors in the two possible forms.
    Used to check the interference between rows.
    6 shapes, flickDelay seconds each one.
    */
void flickerTest () {
  alternativeFill(0,4095,0,0);
  delay(EFFECTS_FLICKDELAY);
  alternativeFill(1,4095,0,0);
  delay(EFFECTS_FLICKDELAY);
  alternativeFill(0,0,4095,0);
  delay(EFFECTS_FLICKDELAY);
  alternativeFill(1,0,4095,0);
  delay(EFFECTS_FLICKDELAY);
  alternativeFill(0,0,0,4095);
  delay(EFFECTS_FLICKDELAY);
  alternativeFill(1,0,0,4095);
  delay(EFFECTS_FLICKDELAY);
}

/** Fills alternatively the matrix with the desired color, and the shape from the two possible.
    \param type, 0 or 1, depending if pixel 0,0 is ON.
    \param r, red value to fill.
    \param g, gren value to fill.
    \param b, blue value to fill.
    */
void alternativeFill (int type, int r, int g, int b) {
  matrix.setMatrix(0,0,0);
  for (uint8_t row = 0; row < NUM_ROWS; row++) {
    for (int pix= 0; pix<8;pix++) {
      if (type) {
        matrix.setPixel(row, pix, r, g, b);
        type=0;
      }
      else {
        type = 1;
      }
    }
    if (type) {
        type=0;
      }
      else {
        type = 1;
      }
  }
}



/** Shift al the pixels in the matrix and introduces the new color from the gradient.
    */
void shiftRGBColors() {
  nextRGBColor(SHOWCASE_SHIFTRGB_STEP);
  shiftColors();
}

/** Shifts all the color in the matrix and add the new one from the color array */
void shiftColors() {
  shiftFilaShift (0);
  matrix.setPixel (0,0, effects_color[0],effects_color[1],effects_color[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  shiftFilaShift(1);
  matrix.setPixel (1,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  
  shiftFilaShift(2);
  matrix.setPixel (2,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  
  shiftFilaShift(3);
  matrix.setPixel (3,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  
  shiftFilaShift(4);
  matrix.setPixel (4,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  
  shiftFilaShift(5);
  matrix.setPixel (5,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  
  shiftFilaShift(6);
  matrix.setPixel (6,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);
  effects_colorsal2[0]=effects_colorsal[0];
  effects_colorsal2[1]=effects_colorsal[1];
  effects_colorsal2[2]=effects_colorsal[2];
  
  shiftFilaShift(7);
  matrix.setPixel (7,0, effects_colorsal2[0],effects_colorsal2[1],effects_colorsal2[2]);  
}


/** Generates the next color in a gradient. Blue->Red->Green->Red again....
    Saves it in global variable color.
    The variable nextRGBColorState should be initialized to 0 in the setup().
    */
void nextRGBColor(uint16_t paso) {
  switch (effects_nextRGBcolorState) {
    case 0:
      effects_color[0]=0;
      effects_color[1]=0;
      effects_color[2]=EFFECTS_RGBCOLORSTART;
      effects_nextRGBcolorState=1;
      break;
    case 1:
      effects_color[0]+=paso;
      effects_color[2]-=paso;
      if (effects_color[2]==0) {
        effects_nextRGBcolorState=2;
      }
        
      break;
    case 2:
      effects_color[1]+=paso;
      effects_color[0]-=paso;
      if (effects_color[0]==0) {
        effects_nextRGBcolorState=3;
      }
      break;
    case 3:
      effects_color[1]-=paso;
      effects_color[2]+=paso;
      if (effects_color[1]==0) {
        effects_nextRGBcolorState=1;
      }
      break;
  } 
}


/** Fills the matrix with random colors.
    It's advisable to initialize the random seed with randomSeed(analogRead(0)) or similar in setup().
    */
void fillRandomColors() {
   for (uint8_t row = 0; row < NUM_ROWS; row++) {
    for (uint8_t pix= 0; pix<NUM_COLS;pix++) {
      matrix.setPixel(row, pix, random(MAX_COLOUR_RANGE +1), random(MAX_COLOUR_RANGE+1), random(MAX_COLOUR_RANGE+1)); 
      
    }
  }
}


/** Does and in to out effect. The new color is taken from color;
    */   
void inToOut() {
  //Big square
  matrix.setRow (0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setRow (7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));  
  
  matrix.setPixel(1,0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(2,0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(3,0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(4,0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(5,0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(6,0,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  
  matrix.setPixel(1,7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(2,7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(3,7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(4,7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(5,7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  matrix.setPixel(6,7,matrix.getPixelR(1,1),matrix.getPixelG(1,1),matrix.getPixelB(1,1));
  
  //Medium square
  
  matrix.setPixel(1,1,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(1,2,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(1,3,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(1,4,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(1,5,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(1,6,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  
  matrix.setPixel(6,1,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(6,2,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(6,3,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(6,4,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(6,5,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(6,6,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  
  matrix.setPixel(2,1,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(3,1,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(4,1,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(5,1,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  
  matrix.setPixel(2,6,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(3,6,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(4,6,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  matrix.setPixel(5,6,matrix.getPixelR(2,2),matrix.getPixelG(2,2),matrix.getPixelB(2,2));
  
  
  
  
  
  
  //Small Square
  matrix.setPixel(2,2,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(2,3,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(2,4,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(2,5,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  
  matrix.setPixel(5,2,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(5,3,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(5,4,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(5,5,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  
  matrix.setPixel(3,2,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(4,2,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(3,5,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  matrix.setPixel(4,5,matrix.getPixelR(3,3),matrix.getPixelG(3,3),matrix.getPixelB(3,3));
  
  
  //New square
  matrix.setPixel(3,3, effects_color[0],effects_color[1],effects_color[2]);
  matrix.setPixel(3,4, effects_color[0],effects_color[1],effects_color[2]);
  matrix.setPixel(4,3, effects_color[0],effects_color[1],effects_color[2]);
  matrix.setPixel(4,4, effects_color[0],effects_color[1],effects_color[2]);
}



/** Creates a light pulse with a color on the entire matrix

    */
void lightPulse() {
   
  for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,0,0);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,0,0);
  }  
  for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(0,i,0);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(0,i,0);
  }  
  for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(0,0,i);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(0,0,i);
  } 
 for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,0,i);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,0,i);
  } 
 for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(0,i,i);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(0,i,i);
  } 
 for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,i,0);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,i,0);
  }
  for (uint16_t i=0; i<SHOWCASE_LIGHTPULSE_MAX;i+=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,i,i);
  } 
  for (uint16_t i=SHOWCASE_LIGHTPULSE_MAX; i>0;i-=SHOWCASE_LIGHTPULSE_STEP) {
    matrix.setMatrix(i,i,i);
  }    
}

