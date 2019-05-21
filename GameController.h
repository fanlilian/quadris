#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_
#include <vector>
#include <iostream>
#include <string>
#include "gameboard.h"
#include "pieceState.h"
#include "textdisplay.h"
#include "block.h"
#include "info.h"
#include "Gamepiece.h"
#include "subject.h"
#include "observer.h"
#include "level.h"
#include <fstream>

class GameController (){
  bool textOnly;
  int seed;
  string sequence;
  int level;
  GameBoard g;
    public:
    GameController(bool textOnly, int seed, string sequence, int level);
    void playGame();
}

#endif
