#include "Matrix.h"

Matrix matrix;
unsigned long previousMillis = 0;
const long interval = 100;

int count = 0;
int dirChange = 5;
int dirChangeIn = 5;
int dir = 1;
void updateDrawing() {
  if(count != 0){
      matrix.drawBoxFilled(0,0,4,count-1);
  }
  count += dir;
  dirChangeIn--;
  if(dirChangeIn == 0) {
    dir *= -1;
    dirChangeIn = dirChange;
  }
}

void setup() {
  
}

void loop() {

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    matrix.clear();
    updateDrawing();
    previousMillis = currentMillis;
  }
  
  matrix.render();
}
