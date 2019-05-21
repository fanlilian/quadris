#include "Gamepiece.h"

Gamepiece::Gamepiece(int level, Shape shape){
  this->level = level;
  this->setState(PieceType::New);
  this->shape = shape;
  this->blocks.resize(4);
  Shape s = this->shape;
  if (s == Shape::I){
    for (int i = 0; i < 4; ++i){
      this->blocks[i].setRow(3);
      this->blocks[i].setCol(i);
      this->blocks[i].setShape(Shape::I);
    }
  }
  else if (s == Shape::J){
    this->blocks[0].setRow(2);
    this->blocks[0].setCol(0);
    this->blocks[0].setShape(Shape::J);
    for (int i = 1; i < 4; ++i){
      this->blocks[i].setRow(3);
      this->blocks[i].setCol(i - 1);
      this->blocks[i].setShape(Shape::J);
    }
  }
  else if (s == Shape::L){
    for (int i = 0; i < 3; ++i){
      this->blocks[i].setRow(3);
      this->blocks[i].setCol(i);
      this->blocks[i].setShape(Shape::L);
    }
    this->blocks[3].setRow(2);
    this->blocks[3].setCol(2);
    this->blocks[3].setShape(Shape::L);
  }
  else if (s == Shape::O){
    for (int i = 0; i < 2; ++i){
      this->blocks[i].setRow(2);
      this->blocks[i].setCol(i);
      this->blocks[i].setShape(Shape::O);
    }
    for (int i = 2; i < 4; ++i){
      this->blocks[i].setRow(3);
      this->blocks[i].setCol(i - 2);
      this->blocks[i].setShape(Shape::O);
    }
  }
  else if (s == Shape::S){
    for (int i = 0; i < 2; ++i){
      this->blocks[i].setRow(3);
      this->blocks[i].setCol(i);
      this->blocks[i].setShape(Shape::S);
    }
    for (int i = 2; i < 4; ++i){
      this->blocks[i].setRow(2);
      this->blocks[i].setCol(i - 1);
      this->blocks[i].setShape(Shape::S);
    }
  }
  else if (s == Shape::T){
    for (int i = 0; i < 3; ++i){
      this->blocks[i].setRow(2);
      this->blocks[i].setCol(i);
      this->blocks[i].setShape(Shape::T);
    }
    this->blocks[3].setRow(3);
    this->blocks[3].setCol(2);
    this->blocks[3].setShape(Shape::T);
  }
  else if (s == Shape::Z){
    for (int i = 0; i < 2; ++i){
      this->blocks[i].setRow(2);
      this->blocks[i].setCol(i);
      this->blocks[i].setShape(Shape::Z);
    }
    for (int i = 2; i < 4; ++i){
      this->blocks[i].setRow(3);
      this->blocks[i].setCol(i - 1);
      this->blocks[i].setShape(Shape::Z);
    }
  }
}

Gamepiece::~Gamepiece(){}

//Take original, swap x and y for all getBlocks
//then multiple all col by -1
// then shift back

//current col (leftmost col)
//newCOl is smallest(most negative col) after flipping negative
// all columns + (current - new)
void Gamepiece::rotateClock(){
  std::vector<Block> temp = this->blocks;
  int newCol;
  bool first = true;
  for (int i = 0; i < 4; ++i){
    int r = temp[i].getInfo().row;
    int c = temp[i].getInfo().col;
    if (c > 17){
      throw InvalidMove();
    }
    if (first){
      newCol = -1 * r;
    }
    else if (-1 * r < newCol){
      newCol = -1 * r;
    }
    temp[i].setRow(c);
    temp[i].setCol(-1 * r);
  }
  for (int i = 0; i < 4; ++i){
    int c = this->blocks[i].getInfo().col;
    int j = c + -1 * newCol;
    if (j > 10){
      throw InvalidMove();
    }
    this->blocks[i].setCol(j);
  }
  for (int i = 0; i < 4; ++i){
    this->blocks[i].setRow(temp[i].getInfo().row);
    this->blocks[i].setCol(temp[i].getInfo().col);
  }
}

void Gamepiece::rotateCounter(int rotations){
  for (int i = 1; i <= rotations; ++i){
    rotateClock();
  }
}

void Gamepiece::down(){
  for (int i = 0; i < 4; ++i){
    int row = this->blocks[i].getInfo().row;
    this->blocks[i].setRow(row - 1);
  }
}

void Gamepiece::left(){
  for (int i = 0; i < 4; ++i){
    int col = this->blocks[i].getInfo().col;
    this->blocks[i].setCol(col - 1);
  }
}

void Gamepiece::right(){
  for (int i = 0; i < 4;++i){
    int col = this->blocks[i].getInfo().col;
    this->blocks[i].setCol(col + 1);
  }
}

std::vector<Block> Gamepiece::getBlocks(){
  return this->blocks;
}

pieceState Gamepiece::getState(){
  return this->state;
}

Shape Gamepiece::getShape(){
  return this->shape;
}

void Gamepiece::setState(PieceType p){
  this->state.piece = p;
}

void Gamepiece::setShape(Shape s){
  this->shape = s;
  for (int i = 0; i < 4; ++i){
      this->blocks[i].setShape(this->shape);
  }
}

int Gamepiece::getLevel(){
  return this->level;
}
