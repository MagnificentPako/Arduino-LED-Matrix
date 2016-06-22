#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

class Matrix {
public:
  Matrix();
  ~Matrix();
  void clear();
  void render();
  void drawPixel(int x, int y);

  //Helper methods
  void drawBox(int x1, int y1, int x2, int y2);
  void drawBoxFilled(int x1, int y1, int x2, int y2);
  void drawLine(int x1, int y1, int x2, int y2); //TODO: Fix this crap
  void drawArray(int mat[5][5]);
  void drawArrayAtPosition(int mat[5][5], int x, int y);
private:
  void setPixel(int x, int y, int mode);
  void clean();
  void resetCounter();
  void resetRows();
  void setLine(int* line);
  void nextLine();
  int interval;
  int mat[5][5];
};

#endif
