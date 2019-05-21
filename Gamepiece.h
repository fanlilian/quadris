#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#include <vector>
#include <iostream>
#include <string>
#include "pieceState.h"
#include "block.h"
#include "info.h"

class InvalidMove {};
class Gamepiece {
protected:
  int level;
  pieceState state;
  Shape shape;
  std::vector<Block> blocks;
public:
  Gamepiece(int level, Shape shape);
  ~Gamepiece();

  void rotateClock();
  void rotateCounter(int rotations);

  void down();
  void right();
  void left();

  std::vector<Block> getBlocks();
  pieceState getState();
  Shape getShape();
  void setState(PieceType p);
  void setShape(Shape s);
  int getLevel();
};

#endif
