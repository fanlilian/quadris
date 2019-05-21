#ifndef _LEVEL_THREE_FOUR_H_
#define _LEVEL_THREE_FOUR_H_
#include "level.h"
#include <string>

class LevelThreeFour: public Level{
  public:
    LevelThreeFour(std::string sequence);
    std::string getShape(int &seed) override;
};

#endif
