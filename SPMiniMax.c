#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth){//TODO what about the -2? and -10?
    if (currentGame==NULL)
        return -1;
    if (maxDepth<=0 || maxDepth > 7)
        return -2;
    SPMiniMaxNode *root = createNode(INT_MIN, INT_MAX, 1,spFiarGameCopy(currentGame),currentGame->currentPlayer, -10);
    SPMiniMaxNode *node = getMove(root, maxDepth);
    if (node ==NULL)
        return -1;
    return node->move+1;
}