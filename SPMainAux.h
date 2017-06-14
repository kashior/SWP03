#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include "SPFIARGame.h"

//put auxiliary functions and constants used by the main function here.
int suggestMove(SPFiarGame *currentGame, unsigned int maxDepth);

void undoMove(SPFiarGame* currentGame);

void addDisc(SPFiarGame* currentGame, int col);

void quit(SPFiarGame* currentGame);

void restartGame(SPFiarGame* currentGame);

bool proccesComand(SPFiarGame* currentGame, SPCommand command, unsigned int maxDepth, char* winner);

char playFIAR(SPFiarGame** game,bool initGame, unsigned int* level);

bool  checkCommandAfterGameisOver(SPCommand command,SPFiarGame** currentGame );

SPCommand gameOver(SPFiarGame** game, char winner);

#endif
