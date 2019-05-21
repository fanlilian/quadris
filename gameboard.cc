#include "gameboard.h"
using namespace std;
// 11 COLUMNS, 15 ROWS (but 3 at the top for rotate space)
int addBlockPts = 0;			// keeps track of how many blocks cleared .. :( for points..
void GameBoard::init(int level){
	this->level = level;
	td = make_shared<TextDisplay>(TextDisplay {make_shared<int>(score), make_shared<int>(hiScore),
		make_shared<int>(level), make_shared<Gamepiece>(nextPiece)});
	// Initialize theBoard by default constructing Blocks.
	for (int r = 0; r < 18; ++r) {
		theBoard.emplace_back(vector<Block>());
		for (int c = 0; c < 11; ++c) {
			theBoard[r].emplace_back(Block {});
		}
		rowCount.emplace_back(0);
	}
	// Set all Blocks to have a top observer ONLY, and td to observe every Block.
	for (int r = 0; r < 18; ++r) {
		for (int c = 0; c < 11; ++c) {
			if (r > 0) {
				theBoard[r][c].attach(make_shared<Block>(theBoard[r-1][c]));	// attach top obs.
			}
			if (c > 0) {
				theBoard[r][c].attach(make_shared<Block>(theBoard[r][c-1]));	// attach right obs.
			}
			theBoard[r][c].attach(td);	// td is an observer of every Block.
		}
	}
}
void GameBoard::setLevel(int level) {
	GameBoard::level = level;
}
void GameBoard::setNextPiece(const Gamepiece &gp) {
	nextPiece = gp;
}
void GameBoard::updateScore(int rowsCleared, int addBlockPts) {
	int rowScore = score + rowsCleared;
	score += rowScore * rowScore + addBlockPts;
	if (score > hiScore) hiScore = score;
}
int calculatePts(int level) {
	int addOne = level + 1;
	return addOne * addOne;
}
void GameBoard::removePBlock(const Block &b) {
	// 1. Iterate through the Gamepieces in thePieces
	// 2. Loop through the blocks in each Gamepiece to check if same piece.
	//    Once the piece has been found, set that Gamepiece's block value to be Empty.
	// 3. Loop through every Gamepiece again, to check if all of the blocks of the Piece
	//    are Empty or not. If so, remove the Piece from thePieces, and increase a
	//    counter that will affect the score.
	int track = 0;	// tracks what place we're in, during thePieces loop.
	for (auto &gp : thePieces) {
		int emptyCount = 0;
		for (int i = 0; i < 4; ++i) {
			Info curBlock = gp.getBlocks()[i].getInfo();
			Info bInfo = b.getInfo();
			if (curBlock.row == bInfo.row && curBlock.col == bInfo.col) {
				gp.getBlocks()[i].setShape(Shape::Empty);
			}
			if (curBlock.shape == Shape::Empty) {
				++emptyCount;
			}
		}
		if (emptyCount == 4) {	// this piece is empty! pop it offfffff.
			addBlockPts += calculatePts(gp.getLevel());
			thePieces.erase(thePieces.begin() + track);
		}
	}
}
void GameBoard::clearRow(vector<int> &rows) {				// FIX THIS FOR ARRAY OF ROWS
	for (auto row : rows) {
		State clear;
		clear.type = StateType::Clear;
		theBoard[row][0].setState(clear);
		theBoard[row][0].notifyObserver();
		for (int c = 0; c < 11; ++c) {
			removePBlock(theBoard[row][c]);
		}
		// Moves the values of rowCount down
		for (int c = row; c >= 0; --c) {
			if (c == 0) {
				rowCount[c] = 0;
			} else {
				rowCount[c] = rowCount[c-1];
			}
		}
	}
}
void GameBoard::checkRows(const vector<Block> &blocks) {
	vector<int> rows;
	for (int i = 0; i < 4; ++i) {
		Block curBlock = blocks[i];
		int r = curBlock.getInfo().row;
		if (rowCount[r] == 11) {
			vector<int>::iterator it;
			it = find(rows.begin(), rows.end(), r);
			if (it != rows.end()) {
				rows.emplace_back(curBlock.getInfo().row);
				sort(rows.begin(), rows.end());
			}
		}
	}
	clearRow(rows);
	int rowsCleared = rows.size();
	if (rowsCleared > 0) updateScore(rowsCleared, addBlockPts);
	addBlockPts = 0;
}
// placePiece places the piece on theBoard, since it is allowed.
void GameBoard::tempPiece(const vector<Block> &blocks) {
	for (int i = 0; i < 4; ++i) {
		Block curBlock = blocks[i];
		Info curInfo = curBlock.getInfo();
		int row = curInfo.row;
		int col = curInfo.col;
		theBoard[row][col].setShape(curInfo.shape);
		td->notify(curBlock);
	}
}
// canPlace checks if the current Block b is occupied on theBoard
bool GameBoard::canPlace(const Block &b) {
	int row = b.getInfo().row;
	int col = b.getInfo().col;
	Shape shape = theBoard[row][col].getInfo().shape;
	if (shape == Shape::Empty) return true;
	return false;
}

// for play, controller will give us
void GameBoard::manipulate(Gamepiece &p) {
	PieceType pState = p.getState().piece;
	vector<Block> blocks = p.getBlocks();
	if (pState == PieceType::New) {	// initializing.
		bool canPut = true;
		for (int i = 0; i < 4; ++i) {
			Block b = blocks[i];
			if (!canPlace(b)) {
				canPut = false;
				break;
			}
		}
		if (canPut == false) {			// basically, we can't perform that mutation.
			throw InvalidMove();
		} else {
			tempPiece(blocks);			// let's put it on our board :)
		}
	} else if (pState == PieceType::Changing) {	// to get rid of the previous piece's position
		for (int i = 0; i < 4; ++i) {
			Info b = blocks[i].getInfo();
			theBoard[b.row][b.col].setShape(Shape::Empty);
			td->notify(theBoard[b.row][b.col]);
		}
	} else if (pState == PieceType::Dropping) {
		Gamepiece temp = p;
		while (true) {
			p.down();
			bool track = true;
			for (int i = 0; i < 4; ++i) {
				Block curBlock = p.getBlocks()[i];
				if (!canPlace(curBlock)) {
					track = false;
					break;
			}
			if (track == false) break;
			temp = p;
		}
		p = temp;
	}
}
	Gamepiece temp = p;
	temp.down();
	bool track = true;
	for (int i = 0; i < 4; ++i) {
		Block curBlock = temp.getBlocks()[i];
		if (!canPlace(curBlock)) {
			track = false;
			break;
		}
	}
	if (track) {					// this piece needs to be placed!
		p.setState(PieceType::Placed);
		thePieces.emplace_back(p);
		for (int i = 0; i < 4; ++i) {
			int row = blocks[i].getInfo().row;
			++rowCount[row];
		}
		checkRows(blocks);				// get rid of rows
	}
}
ostream &operator<<(ostream &out, const GameBoard &g) {
	out << g.td;
	return out;
}
