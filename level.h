#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <string>

/* this is an abstract class that strictly handles giving the controller a
shape. The derived classes of this class will handle probability skewed pieces
but not with behaviour of each piece. THe behaviour will be dealt with in the
controller.*/

class Level{
	std::string sequence;
  public:
	Level(std::string sequence);
	virtual std::string getShape(int &seed);                                   // pure virtual function that returns to the controller a shape.
};

#endif
