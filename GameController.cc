#include "GameController.h"

GameController::GameController(bool textOnly, int seed,
    string scriptFile, int level): textOnly{textOnly}, seed{seed},
        sequence{sequence}, level{level} {}

Shape convertShape(String s){
  if (s == "I"){
    return Shape::I;
  }
  else if (s == "J"){
    return Shape::J;
  }
  else if (s == "L"){
    return Shape::L;
  }
  else if (s == "O"){
    return Shape::O;
  }
  else if (s == "S"){
    return Shape::S;
  }
  else if (s == "T"){
    return Shape::T;
  }
  else if (s == "Z"){
    return Shape::Z;
  }
}

void GameController::playGame(){
  String cmd;
  Shape c, n;
  int index = 0;
  int size = this->sequence.length();
  bool random = true;
  bool beginGame = true;

  g.init(this->level);

  Gamepiece current {this->level,Shape::Empty};
  Gamepiece next {this->level, Shape::Empty};
  //outer loop
  while (true){
      //if level is 0
      if (this->level == 0 || random == false ){
        if (index >= size){
          break;
        }
        if (beginGame){
            c = convertShape(this->sequence[index]);
            beginGame = false;
            current.setShape(c);
            ++index;
        }
        else {
            current = next;
        }
        if (index < size){
          n = getShape(this->sequence[index]);
          next.setShape(n);
          ++index;
        }
      }
      //if level is 1
      else if (this->level == 1){
        LevelOne level {&seed};
        c = level.getShape();
        n = level.getShape();
      }
      //if level is 2
      else if (this->level == 2){
        LevelTwo level {&seed};
        c = level.getShape();
        n = level.getShape();
      }
      //if level is 3
      else if (this->level == 3){
        LevelTwo level {&seed};
        c = level.getShape();
        n = level.getShape();
      }
      //if level is 4
      else if (this->level == 4){
        LevelTwo level {&seed};
        c = level.getShape();
        n = level.getShape();
      }

      //The above was just to determine how to declare the right GamePiece
      // p based on what level it is. Now we read in commands and manipulate
      // the gameboard
      while (true){
        State New {PieceType::New};
        State Changing {PieceType::Changing};
        State Dropping {PieceType::Dropping};
        State Placed {PieceType::Placed};
        cin >> cmd;
        if (cmd == "left"){
          try {
            p.setState(PieceType::changing);
            p.left();
            g.manipulate(p);
          }
          catch (InvalidMove &i){}
        }
        else if (cmd == "right"){
          try {
            p.setState(PieceType::changing);
            p.right();
            g.manipulate(p);
          }
          catch (InvalidMove &i){}
        }
        else if (cmd == "down"){
          try {
            p.setState(PieceType::changing);
            p.down();
            g.manipulate(p);
          }
          catch (InvalidMove &i){}
        }
        else if (cmd == "clockwise"){
          try {
            p.setState(PieceType::changing);
            p.rotateClock();
            g.manipulate(p);
          }
          catch (InvalidMove &i){}
        }
        else if (cmd == "counterclockwise"){
          try {
            p.setState(PieceType::changing);
            p.rotateCounter(3);
            g.manipulate(p);
          }
          catch (InvalidMove &i){}
        }
        else if (cmd == "drop"){
            current.setState(Dropping);
            g.manipulate(current);
            break;
        }
        else if (cmd == "levelup"){
          if (this->level < 4){
            this->level++;
          }
        }
        else if (cmd == "leveldown"){
          if (this->level > 0){
            this->level--;
          }
        }
        else if (cmd == "norandom"){
          random = false;
          index = 0;
        }
        else if (cmd == "random"){
          random = true;
        }
        else if (cmd == "sequence"){
          executeSeq();
        }
        else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" ||
        cmd == "S" || cmd == "T" || cmd == "Z"){
          p = getPiece(cmd, this->level);
        }
        else if (cmd == "restart"){

        }
        else if (cmd == "hint"){

        }
      }
    }
}
