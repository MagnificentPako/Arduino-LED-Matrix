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
void Matrix::drawLine(int x1, int y1, int x2, int y2) {

  int sx, sy, ex, ey, minx, miny, maxx, maxy, xdiff, ydiff;

  sx = floor(x1);
  sy = floor(y1);
  ex = floor(x2);
  ey = floor(y2);

  if(sx == ex && sy == ey) {
    drawPixel(sx,sy);
    return;
  }

  minx = sx > ex ? ex : sx;

  if(minx == sx) {
    miny = sy;
    maxx = ex;
    maxy = ey;
  }else{
    miny = ey;
    maxx = sx;
    maxy = sy;
  }

  xdiff = maxx - minx;
  ydiff = maxy - miny;

  if(xdiff > abs(ydiff)) {

    int y = miny;
    int dy = ydiff / xdiff;
    for(int x = minx; x < maxx; x++) {
      drawPixel(x, floor(y + 0.5));
      y = y + dy;
    }

  }else{

    int x = minx;
    int dx = xdiff / ydiff;
    if(maxy >= miny) {

      for(int y = miny; y < maxy; y++) {
        drawPixel(floor(x+ 0.5),y);
        x = x + dx;
      }

    }else{

      for(int y = miny; y>maxy; y--) {
        drawPixel(floor(x + 0.5),y);
        x = x - dx;
      }

    }

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
