#include <stdio.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame *currentGame, unsigned int maxDepth) {
    if (currentGame == NULL)
        return -1;
    if (maxDepth <= 0 || maxDepth > 7)
        return -1;
    SPFiarGame *copy = spFiarGameCopy(currentGame);
    if (copy == NULL)
        return -2;
    SPMiniMaxNode *root = createNode(INT_MIN, INT_MAX, 1, copy, currentGame->currentPlayer, -1);
    if (root == NULL)
        return -2;
    SPMiniMaxNode *node = getMove(root, maxDepth);
    if (node == NULL)
        return -2;
    return node->move;
}

int computerMove(SPFiarGame *currentGame, unsigned int maxDepth, char *winner) {
    int col = spMinimaxSuggestMove(currentGame, maxDepth);
    if (col == -2)
        return -2;
    spFiarGameSetMove(currentGame, col);
    winner[0] = spFiarCheckWinner(currentGame);

    return col;
}