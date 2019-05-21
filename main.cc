#include <sstream>
#include <string>
int main(int argc, char *argv[]){
    bool textOnly = false;                                                      // Default value to both text and graphics display.
    int seed = 1;                                                               // Default seed is 1.
    std::string defaultScriptFile = "sequence.txt";                             // Default sequence file.
    srd::string sequence;
    int startLevel = 0;                                                         // Default level is 0.
    for (int i = 1; i < argc ; ++i){
        if ( argv[i] == "-text" ){                                              // check for text only mode
            textOnly = true;                                                        // set the bool to true
        }
        else if (argv[i] == "-seed"){                                          // check for a change of seeds
            int newSeed;                                                            // int used to set new seed.
            istringstream ss1(argv[i+1]);                                           // Under assumption of valid input, the next argument should be a seed number
            if (ss1 >> newSeed){                                                     // convert the number string to an int if possible
                seed = newSeed;                                                         // change the seed
                ++i;                                                                    // increment so we don't check the next argument which is a number string
            }
            // if ss1 is not an int then do nothing and use the default seed
        }
        else if (argv[i] == "-scriptfile"){                                     // check for a change of sequence file
            ifstream file(argv[i+1]);
            std::string s;
            if (file >> s){                                                         // if file exists
                sequence = s;                                                       // set the sequence to that of the file
                ++i;                                                                // increment so we don't check the next argument which is a file name
            }
            else {                                                                  // if file doesn't exist
                ifstream sequenceFile(defaultScriptFile);                           // use the defautl sequence in sequence.txt
                sequenceFile >> sequence;                                           // read squence.txt  into the sequence string
            }
        }
        else if (argv[i] == "-startlevel"){                                     // check for a change of starting level
            int newStartLevel;
            istringstream ss2(argv[i+1]);                                           // Under assumption of valid input, the next argument should be a level number
            if (ss2 >> newStartLevel){                                              // convertt the number string to an int if possible
                startLevel = newStartLevel;                                         // change the starting level
                ++i;                                                                // increment so we don't check the next argument which is a level number
            }
            // if ss2 is not an int the do nothing and use the default startLevel
        }
        // if argument is passed is not any of these arguments then do nothing.
    }
    gameController GC(textOnly, seed, sequence, newLevel);                             // Calls GamePlay (our Controller) and gives it the new values
    GC.playGame();
}
