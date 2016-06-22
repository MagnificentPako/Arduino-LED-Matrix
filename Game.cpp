#include "Arduino.h"
#include "Game.h"
#include "Matrix.h"

Matrix matrix;
long lastMillis = 0;

//Die Zeit zwischen jeder Frame
long Game::delta() {
  return millis()-lastMillis;
}

//Rendert die Matrix
void Game::draw() {
  matrix.render();
}

/* Variablen die für das Spiel benötigt werden */

//PIXEL ART FTW
int numbers[4][5][5] = {
  {
    {0,1,1,1,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0}
  },
  {
    {0,0,1,0,0},
    {0,1,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,1,1,1,0}
  },
  {
    {0,1,1,1,0},
    {1,0,0,0,1},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {1,1,1,1,1}
  },
  {
    {1,1,1,1,0},
    {0,0,0,0,1},
    {0,1,1,1,0},
    {0,0,0,0,1},
    {1,1,1,1,0}
  }
};

int player[2] = {2,2}; //x,y
int apple[2] = {floor(random(5)),floor(random(5))}; //x,y
int direction = 0; // 0 = up, 1 = right, 2 = down, 3 = right
boolean ingame = false;

//menu specific
int selected = 0;
boolean transition = false;
int transitionOutPosition = 0;
int transitionInPosition = 4;
int transAdd = 0;

//game specific
long oldMillis = 0;
long interv;
int trailLength = 0;
int trailPositions[25][2] = {}; //Es wird niemals mehr als 25 sein.

/*                                             */

void Game::updateLogic() {
  /* Hier kommt der Code hin der das Spiel "aktualisiert" */
  int input = Serial.available() > 0 ? Serial.read() : -1;
  if(ingame) { //Logik des Spiels

    long currentMillis = millis();

    if(input == 6) {
      ingame = false;
    }

    direction = (input != -1 && input < 5) ? input : direction;

    int ox = player[0];
    int oy = player[1];

    if(player[0] == apple[0] && player[1] == apple[1]) {
      apple[0] = floor(random(5));
      apple[1] = floor(random(5));
      trailPositions[trailLength][0] = ox;
      trailPositions[trailLength][1] = oy;
      trailLength += 1;
    }

    if(currentMillis-oldMillis >= interv) {
      oldMillis = currentMillis;

      int trailBuffer[25][2];
      for(int i = 1; i < trailLength; i++) {
        trailBuffer[i-1][0] = trailPositions[i][0];
        trailBuffer[i-1][1]= trailPositions[i][1];
        trailBuffer[trailLength][0] = player[0];
        trailBuffer[trailLength][1] = player[1];
      }

      for(int i = 0; i < trailLength; i++) {
        trailPositions[i][0] = trailBuffer[i][0];
        trailPositions[i][1] = trailBuffer[i][1];
      }

      switch(direction) {
        case 0: {
          player[1] -= 1;
          return;
        }
        case 1: {
          player[0] += 1;
          return;
        }
        case 2: {
          player[1] += 1;
          return;
        }
        case 3: {
          player[0] -= 1;
          return;
        }
      }

    }

  }else{ //Logik des Menüs
    if(input != -1) {
      Serial.write(input);
      switch (input) {
        case 0: {
          if(selected -1 != -1){
            transition = true;
            transAdd = -1;
          }
          return;
        }
        case 2: {
          if(selected +1 != 4){
            transition = true;
            transAdd = 1;
          }
          return;
        }
        case 5: {
          ingame = true;
          switch(selected) {
            case 0: {interv = 500; return;}
            case 1: {interv = 400; return;}
            case 2: {interv = 200; return;}
            case 3: {interv = 0; return;}
          }
          return;
        }
      }
    }

    if(transition) {
      transitionOutPosition -= 1;
      transitionInPosition -= 1;
      if(transitionInPosition == 0) {
        transition = false;
        transitionInPosition = 4;
        transitionOutPosition = 0;
        selected += transAdd;
        transAdd = 0;
      }
    }

  }
  /*                                                      */
}

void Game::updateDrawing() {
  lastMillis = millis();
  matrix.clear();

  /* Hier kommt der Code hin der das Spiel "zeichnet" */
  if(ingame){
    if(player[0] <= -1) {player[0] = 4;}
    if(player[0] >= 5) {player[0] = 0;}
    if(player[1] <= -1) {player[1] = 4;}
    if(player[1] >= 5) {player[1] = 0;}
    matrix.drawPixel(player[0], player[1]);
    matrix.drawPixel(apple[0], apple[1]);
    if(trailLength > 0) {
      for(int i = 0; i < trailLength; i++) {
        matrix.drawPixel(trailPositions[i][0],trailPositions[i][1]);
      }
    }
  }else{
    if(!transition){
      matrix.drawArray(numbers[selected]);
    }else{
      matrix.drawArrayAtPosition(numbers[selected],transitionOutPosition,0);
      matrix.drawArrayAtPosition(numbers[selected+1],transitionInPosition,0);
    }
  }
  /*                                                  */

}


//Constructor
Game::Game() {
  lastMillis = millis();
  randomSeed(analogRead(1));
}

Game::~Game() {}
