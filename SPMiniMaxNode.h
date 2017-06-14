#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"

//Definitions


typedef struct sp_minimax_node {
    int alpha;
    int beta;
    bool isMaxType;
    SPFiarGame *game;
    char player;
    int move;
    //You May add any fields you like
} SPMiniMaxNode;


int scoringFunction(SPFiarGame *currentGame, SPMiniMaxNode *node);

SPMiniMaxNode *createNode(int alpha, int beta, bool isMaxType, SPFiarGame *copyOfGame, char player, int move);

void updateAlphaBeta(SPMiniMaxNode *root, unsigned int maxDepth, char totalRootPlayer);

SPMiniMaxNode *getMove(SPMiniMaxNode *root, unsigned int maxDepth);

char getOtherPlayer(char player);


#endif
