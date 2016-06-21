#include "Matrix.h"
#include "Game.h"

/*Matrix matrix;
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
*/

Game game;

unsigned long previousMillis = 0;
const long interval = 100;
boolean synced = false;

void setup() {
  Serial.begin(9600);
}



void loop() {

  if(synced) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval){
      game.updateDrawing();
      game.updateLogic();
      previousMillis = currentMillis;
    }
    game.draw();
  }else{
    if(Serial.available()) {
      byte str = Serial.read();
      if(str == 97) {
        Serial.write(11);
        synced = true;
      }
    }
  }

}
