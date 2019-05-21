#include "levelOne.h"
#include <string>
#include <stdlib.h>

/* Level One :
All block selectors will choose a bloock with proabability skewed such that
S and Z blocks are selected with probability 1/12 each, and the other blocks
are selected with probability 1/6 each

I-block = 1/6   {1,2}
J-block = 1/6   {3,4}
L-block = 1/6   {5,6}
O-block = 1/6   {7,8}
S-block = 1/12  {9}
Z-block = 1/12  {10}
T-block = 1/6   {11,12}
        = 1 (STATS230 tells me I'm not missing a piece)
*/

LevelOne::LevelOne(std::string sequence) : Level{sequence}{}


std::string LevelOne::getShape(int &seed){
    srand(seed);                                                                // intialize to seed
    int secret = rand() % 12 + 1;                                               // generate secret number from 1 to 12
    seed = secret;
    if ((secret == 1)||(secret ==2)){                                           // I-block
        return "I";
    }
    else if ((secret == 3)||(secret == 4)){                                     // J-block
        return "J";
    }
    else if ((secret == 5)||(secret == 6)){                                     // L-block
        return "L";
    }
    else if ((secret == 7)||(secret == 8)){                                     // O-block
        return "O";
    }
    else if (secret == 9){                                                      // S-block
        return "S";
    }
    else if (secret == 10){                                                     // Z-block
        return "Z";
    }
    else{                                                                       // T-block
        return "T";
    }
}
