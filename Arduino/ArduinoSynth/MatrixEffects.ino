#define EFFECTS_FLICKDELAY 200
#define EFFECTS_RGBCOLORSTART 4000
#define EFFECTS_CHECKDELAY 100

/** Draws each column with a different colour */
void initialDraw () {
  matrix.setCol(0,926,1384,2032);
  matrix.setCol(1,1528,1144,2024);
  matrix.setCol(2,520,800,1936);
  matrix.setCol(3,304,1224,64);
  matrix.setCol(4,1664,912,144);
  matrix.setCol(5,1992,472,56);
  matrix.setCol(6,1648,232,184);
  matrix.setCol(7,760,1320,2024); 
}

/** Draws a check in the matrix, with delays between each point */
void drawCheck() {
  matrix.setPixel(5,1,0,4095,0);
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(6,2,0,4095,0);
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(5,3,400,4095,0);
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(4,4,800,4095,0);
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(3,5,1200,4095,0);
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(2,6,1600,4095,0);  
}

void drawAS() {
  matrix.setPixel(6,0,4095,0,0); 
  matrix.setPixel(6,4,4095,0,0); 
  matrix.setPixel(6,5,0,0,4095); 
  matrix.setPixel(2,7,0,0,4095); 

  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(5,0,4095,0,0); 
  matrix.setPixel(5,4,4095,0,0);
  matrix.setPixel(6,6,0,0,4095); 
  matrix.setPixel(2,6,0,0,4095);
  
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(4,0,4095,0,0); 
  matrix.setPixel(4,4,4095,0,0);
  matrix.setPixel(3,5,0,0,4095); 
  matrix.setPixel(5,7,0,0,4095);
   
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(3,0,4095,0,0); 
  matrix.setPixel(3,4,4095,0,0); 
  matrix.setPixel(4,1,4095,0,0); 
  matrix.setPixel(4,3,4095,0,0); 
  matrix.setPixel(4,6,0,0,4095); 
  matrix.setPixel(0,0,0,4095,0);
  matrix.setPixel(7,7,0,4095,0); 
  matrix.setPixel(0,7,0,4095,0);
  matrix.setPixel(7,0,0,4095,0); 
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(2,0,4095,0,0); 
  matrix.setPixel(2,4,4095,0,0); 
  matrix.setPixel(4,2,4095,0,0); 
  matrix.setPixel(0,1,0,4095,0);
  matrix.setPixel(7,6,0,4095,0); 
  matrix.setPixel(0,6,0,4095,0);
  matrix.setPixel(7,1,0,4095,0);  
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(1,1,4095,0,0); 
  matrix.setPixel(1,3,4095,0,0);
  matrix.setPixel(0,2,0,4095,0);
  matrix.setPixel(7,5,0,4095,0); 
  matrix.setPixel(0,5,0,4095,0);
  matrix.setPixel(7,2,0,4095,0);  
  delay(EFFECTS_CHECKDELAY);
  matrix.setPixel(1,2,4095,0,0);
  matrix.setPixel(0,3,0,4095,0);
  matrix.setPixel(7,4,0,4095,0); 
  matrix.setPixel(0,4,0,4095,0);
  matrix.setPixel(7,3,0,4095,0); 
 
 
  
}


    
