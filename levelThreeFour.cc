#include "levelThreeFour.h"
#include <string>
#include <stdlib.h>
/* Level Three and Four : 
The block selector will reandomly choose a block with probabilities skewed
such that S and Z blocks are selected with probaility 2/9 each, and the other
blocks are selected with probability 1/9 each.

I-block = 1/9 {1}
J-block = 1/9 {2}
L-block = 1/9 {3}
O-block = 1/9 {4}
S-block = 2/9 {5,6}
Z-block = 2/9 {7,8}
T-block = 1/9 {9}
        = 1
*/
LevelThreeFour::LevelThreeFour (std::string sequence): Level{sequence} {}

std::string LevelThreeFour::getShape(int &seed){
    srand(seed);
    int secret = rand() % 9 + 1;
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
    else if ((secret == 5) || (secret == 6)){
        return "S";
    }
    else if ((secret == 7) || (secret == 8)){
        return "Z";
    }
    else{
        return "T";
    }
}
