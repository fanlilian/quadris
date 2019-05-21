#include "levelTwo.h"
#include <string>
#include <stdlib.h>

/* Level Two : 
All blocks are selected with equal probability.

I-block = 1/7 {1}
J-block = 1/7 {2}
L-block = 1/7 {3}
O-block = 1/7 {4}
S-block = 1/7 {5}
Z-block = 1/7 {6}
T-block = 1/7 {7}
        = 1
*/

LevelTwo::LevelTwo(std::string sequence) : Level{sequence} {}

std::string LevelTwo::getShape(int &seed){
    srand(seed);
    int secret = rand() % 7 + 1;
    seed = secret;
    if (secret == 1){
        return "I";
    }
    else if (secret == 2){
        return "J";
    }
    else if (secret == 3){
        return "L";
    }
    else if (secret == 4){
        return "O";
    }
    else if (secret == 5){
        return "S";
    }
    else if (secret == 6){
        return "Z";
    }
    else{
        return "T";
    }
}
