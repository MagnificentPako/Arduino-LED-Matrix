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
int dim = 0;
int dim2 = 0;
int threshhold = 4;
int dir = 1;
int dir2 = 0;
/*                                             */

void Game::updateLogic() {
  /* Hier kommt der Code hin der das Spiel "aktualisiert" */

    if(dim == threshhold && dir2 != -1) {
      dir = 0;
      dir2 = 1;
    }

    if(dim2 == threshhold && dir2 == 1) {
      dir = 0;
      dir2 = -1;
    }

    if(dim2 == 0 && dir2 == -1) {
      dir2 = 0;
      dir = -1;
    }

    if(dim2 == 0 && dim == 0) {
      dir = 1;
    }

    dim = dim + dir;
    dim2 += dir2;

  /*                                                      */
}

void Game::updateDrawing() {
  lastMillis = millis();
  matrix.clear();

  /* Hier kommt der Code hin der das Spiel "zeichnet" */
    matrix.drawBoxFilled(dim2,dim2,dim,dim);
  /*                                                  */

}


//Constructor
Game::Game() {
  lastMillis = millis();
}

Game::~Game() {}
