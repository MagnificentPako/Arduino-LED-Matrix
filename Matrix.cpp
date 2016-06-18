#include "Arduino.h"
#include "Matrix.h"

const int CADD = 8;
const int CRES = 9;
const int ROWS[5] = {1,2,3,4,5};

int mat[5][5] = {
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};

long interval = 100;

//Setzt Counter IC zurück
void Matrix::resetCounter() {
  digitalWrite(CRES, HIGH);
  delayMicroseconds(100);
  digitalWrite(CRES, LOW);
}

//Setzt "Rows" zurück
void Matrix::resetRows() {
  for(int i = 0; i < 5; i++) {
    digitalWrite(ROWS[i], LOW);
  }
}

//Setzt Matrix zurück, aber lässt das Array so wie es ist
void Matrix::clean() {
  resetCounter();
  resetRows();
}

//Setzt komplette Matrix zurück
void Matrix::clear() {
  clean();
  for(int i = 0; i<5; i++) {
    for(int j = 0; j<5; j++) {
      mat[i][j] = 0;
    }
  }
}

//Geht eine "Line" weiter
void Matrix::nextLine() {
  digitalWrite(CADD, HIGH);
  delayMicroseconds(50);
  digitalWrite(CADD, LOW);
  delayMicroseconds(1000-50);
}

//Setzt einen Pixel
void Matrix::setPixel(int x, int y, int mode) {
  mat[x][y] = mode;
}

void Matrix::drawPixel(int x, int y) {
  setPixel(x,y,HIGH);
}

//Setzt eine "Line"
void Matrix::setLine(int* line) {
  resetRows();
  for(int i = 0; i < 5; i++) {
    digitalWrite(ROWS[i], line[i]);
  }
}

//Überträgt den Inhalt des "Buffers" auf die Matrix
void Matrix::render() {
  clean();
  for(int i = 0; i < 5; i++) {
    if(i>0){nextLine();}
    setLine(mat[i]);
    delay(1);
    resetRows();
  }
}

//Zeichenmethoden

//Zeichnet eine Box (bzw. einen Rahmen) auf die Matrix
void Matrix::drawBox(int x1, int y1, int x2, int y2) {
  for(int y = y1; y<=y2; y++) {
    if(y == y1 || y == y2) {
      for(int i = x1; i<=x2; i++){
        drawPixel(i,y);
      }
    }else{
      drawPixel(x1,y);
      drawPixel(x2,y);
    }
  }
}

//Zeichnet eine gefüllte Box
void Matrix::drawBoxFilled(int x1, int y1, int x2, int y2) {
  for(int y = y1; y<=y2; y++) {
    for(int i = x1; i<=x2; i++){
      drawPixel(i,y);
    }
  }
}

//Zeichnet eine Linie
//http://c.happycodings.com/games-and-graphics/code18.html
void Matrix::drawLine(int x1, int y1, int x2, int y2) {
  int dx, dy, p ,end;
  float x, y;

  dx = abs(x1 - x2);
  dy = abs(y1 -  y2);
  p = 2 * dy - dx;
  if(x1 > x2) {
    x = x2;
    y = y2;
     end = x1;
  }else{
    x = x1;
    y = y1;
    end = x2;
  }
  drawPixel(x,y);
  while(x < end) {
    x += 1;
    if(p < 0) {
      p = p+2*dy;
    }else{
      y = y+1;
      p = p+2*(dy-dx);
    }
    drawPixel(x,y);
  }
}

//Constructor and Destructor
Matrix::Matrix() {
  pinMode(CADD, OUTPUT);
  pinMode(CRES, OUTPUT);
  for(int i = 0; i < 5; i++) {
    pinMode(ROWS[i], OUTPUT);
  }
  clear();
  resetCounter();
}

Matrix::~Matrix() {}
