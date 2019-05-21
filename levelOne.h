#ifndef _LEVEL_ONE_H_
#define _LEVEL_ONE_H_
#include "level.h"
#include <string>
#include <memory>

class LevelOne: public Level{
  public:
	LevelOne(std::string sequence);
    	std::string getShape(int &seed) override;
};

#endif
