#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"

//Definitions


typedef struct sp_minimax_node {
    int alpha;
    int betha;
    bool isMaxType;
    int score;
    SPFiarGame *game;
    char player;
    //You May add any fields you like
} SPMiniMaxNode;


int scoringFunction(SPFiarGame *currentGame, SPMiniMaxNode node);

#endif
