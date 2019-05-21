#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "subject.h"
#include "Gamepiece.h"

class Cell;
class TextDisplay: public Observer<Info, State> {
	std::shared_ptr<int> score, hiScore, level;
	std::shared_ptr<Gamepiece> nextPiece;
	std::vector<std::vector<char>> theDisplay;
 public:
	TextDisplay(std::shared_ptr<int> score, std::shared_ptr<int> hiScore,
		 std::shared_ptr<int>level, std::shared_ptr<Gamepiece> nextPiece);
	void notify(Subject<Info, State> &whoNotified) override;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
