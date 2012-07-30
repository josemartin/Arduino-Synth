
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
  delay(100);
  matrix.setPixel(6,2,0,4095,0);
  delay(100);
  matrix.setPixel(5,3,400,4095,0);
  delay(100);
  matrix.setPixel(4,4,800,4095,0);
  delay(100);
  matrix.setPixel(3,5,1200,4095,0);
  delay(100);
  matrix.setPixel(2,6,1600,4095,0);  
}

