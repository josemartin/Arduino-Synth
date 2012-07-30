/* Does the startup animation */
void startupAnimation() {
  initialDraw ();
  delay(700);
  matrix.setMatrix(0,0,0);
  drawAS();
  delay(900);
  matrix.setMatrix(0,0,0);
  drawCheck();
  delay(500);
  matrix.setMatrix(0,0,0);
}

 
