#include "level.h"

Level::Level (std::string sequence) : sequence{sequence}{}

std::string Level::getShape(int &seed){
	std::string piece;
	piece = sequence[seed];
	seed++;
	return piece;	// let the controller deal with selecting the shape
}
