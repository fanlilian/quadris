#ifndef _LEVEL_TWO_H_
#define _LEVEL_TWO_H_
#include "level.h"
#include <string>

class LevelTwo: public Level{
  public:
    LevelTwo(std::string sequence);
    std::string getShape(int &seed) override;
};

#endif
