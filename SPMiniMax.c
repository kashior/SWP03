#include <stdio.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth){
    if (currentGame==NULL)
        return -1;
    if (maxDepth<=0 || maxDepth > 7)
        return -1;
    SPMiniMaxNode *root = createNode(INT_MIN, INT_MAX, 1,spFiarGameCopy(currentGame),currentGame->currentPlayer, -1);
    SPMiniMaxNode *node = getMove(root, maxDepth);
    if (node ==NULL)
        return -1;
    return node->move;
}
int computerMove(SPFiarGame* currentGame, unsigned int maxDepth, char* winner){
    int col=spMinimaxSuggestMove(currentGame,maxDepth);
    spFiarGameSetMove(currentGame,col);
    winner[0]=spFiarCheckWinner(currentGame);

    return col;
}