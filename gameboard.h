#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_
#include "block.h"
#include "textdisplay.h"
#include "Gamepiece.h"
#include "EmptyPiece.h"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

// A GameBoard has 11 columns and 15 rows.
class GameBoard {
	int score = 0, hiScore = 0, level;
	std::vector<int> rowCount;		// 2d array to keep track of num of blocks in each row
	std::vector<std::vector<Block>> theBoard;
	std::vector<Gamepiece> thePieces;
	Gamepiece nextPiece;
	std::shared_ptr<TextDisplay> td;
	void checkRows(const std::vector<Block> &blocks);
	void clearRow(std::vector<int> &rows);
	void updateScore(int rowsCleared, int addBlockPts);
	void removePBlock(const Block &b);
	bool canPlace(const Block &b);
	void tempPiece(const std::vector<Block> &blocks);
 public:
	void init(int level = 0);
	void setLevel(int level);
	void setNextPiece(const Gamepiece &gp);
	void manipulate(Gamepiece &b);
	friend std::ostream &operator<<(std::ostream &out, const GameBoard &g);
};

#endif
