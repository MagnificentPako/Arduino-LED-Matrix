#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

class Game {
public:
  Game();
  ~Game();
  void updateLogic();
  void updateDrawing();
  void draw();
private:
  long delta();
};

#endif
