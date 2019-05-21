#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(shared_ptr<int> score, shared_ptr<int> hiScore,
	 shared_ptr<int> level, shared_ptr<Gamepiece> nextPiece) {
	TextDisplay::score = score;
	TextDisplay::hiScore = hiScore;
	TextDisplay::level = level;
	TextDisplay::nextPiece = nextPiece;
	for (int r = 0; r < 18; ++r) {
		theDisplay.emplace_back(vector<char>());
		for (int c = 0; c < 11; ++c) {
			theDisplay[r].emplace_back(' ');
		}
	}
}
void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	// whoNotified is the Block that TextDisplay has been notified of.
	Info info = whoNotified.getInfo();
	Shape shape = info.shape;
	char c;
	if (shape == Shape::T) c = 'T';
	else if (shape == Shape::L) c = 'L';
	else if (shape == Shape::J) c = 'J';
	else if (shape == Shape::S) c = 'S';
	else if (shape == Shape::Z) c = 'Z';
	else if (shape == Shape::I) c = 'I';
	else if (shape == Shape::O) c = 'O';
	else c = ' ';
	theDisplay[info.row][info.col] = c;
}
// Returns the number of digits a number, num, has. Purely for the purpose of
// making the printed display look in-line.
int Digits(int num) {
	if (num == 0) return 1;
	int digits = 0;
	while (num != 0) {
		num = num / 10;
		++digits;
	}
	return digits;
}
void printShape(const Shape &shape) {
	if (shape == Shape::I) {
		cout << "IIII" << endl;
	} else if (shape == Shape::J) {
		cout << "J" << endl;
		cout << "JJJ" << endl;
	} else if (shape == Shape::L) {
		cout << "  L" << endl;
		cout << "LLL" << endl;
	} else if (shape == Shape::O) {
		cout << "OO" << endl;
		cout << "OO" << endl;
	} else if (shape == Shape::S) {
		cout << " SS" << endl;
		cout << "SS " << endl;
	} else if (shape == Shape::Z) {
		cout << "ZZ " << endl;
		cout << " ZZ" << endl;
	} else if (shape == Shape::T) {
		cout << "TTT" << endl;
		cout << " T " << endl;
	}
}
ostream &operator<<(ostream &out, const TextDisplay &td) {
	out << "Level:      " << *td.level << endl;
	out << "Score:";
	int scSpace = Digits(*td.score);
	int hiSpace = Digits(*td.hiScore);
	for (int i = 0; i < 7 - scSpace; ++i) {
		out << " ";
	}
	out << *td.score << endl;
	for (int j = 0; j < 7 - hiSpace; ++j) {
		out << " ";
	}
	out << *td.hiScore << endl;
	out << "-----------" << endl;			// should be 11 dashes.
	for (int r = 0; r < 18; ++r) {
		for (int c = 0; c < 11; ++c) {
			out << td.theDisplay[r][c];
		}
		out << endl;
	}
	out << "-----------" << endl;
	out << "Next:" << endl;
	printShape(td.nextPiece->getShape());
	return out;
}
