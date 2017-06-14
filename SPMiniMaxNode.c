#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"

const int VECTOR[2*(SP_FIAR_GAME_SPAN-1)] ={-5,-2,-1,1,2,5};

SPMiniMaxNode *createNode(int alpha, int beta, bool isMaxType, SPFiarGame *copyOfGame, char player, int move) {
    SPMiniMaxNode *node = (SPMiniMaxNode *)malloc(sizeof(SPMiniMaxNode));
    if (node ==NULL)
        return NULL;
    node->alpha = alpha;
    node->beta = beta;
    node->isMaxType = isMaxType;

    node->game = copyOfGame;
    node->player = player;
    node->move = move;
    return node;
}

void updateFirstSpanCounter(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row][col] == node->player)
        (*counter)++;
    else if (src->gameBoard[row][col] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)--;
}

void updateSpanCounter(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row][col - 1] == node->player)
        (*counter)--;
    else if (src->gameBoard[row][col - 1] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row][col + SP_FIAR_GAME_SPAN - 1] == node->player)
        (*counter)++;
    else if (src->gameBoard[row][col + SP_FIAR_GAME_SPAN - 1] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)--;
}

void updateSpanCounterTranspose(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row -1][col] == node->player)
        (*counter)--;
    else if (src->gameBoard[row -1][col] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col ] == node->player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col ] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)--;
}

void updateDiagLTR(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row-1][col - 1] == node->player)
        (*counter)--;
    else if (src->gameBoard[row-1][col - 1] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col + SP_FIAR_GAME_SPAN - 1] == node->player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col + SP_FIAR_GAME_SPAN - 1] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)--;
}

void updateDiagRTL(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row-1][col + 1] == node->player)
        (*counter)--;
    else if (src->gameBoard[row-1][col + 1] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col - SP_FIAR_GAME_SPAN + 1] == node->player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col - SP_FIAR_GAME_SPAN + 1] != SP_FIAR_GAME_EMPTY_ENTRY) // it is the opponent!
        (*counter)--;
}

void incrementCellPerSpan(int counter, int *array){
    if (counter > 0)
        array[counter + 2]++;
    else if (counter < 0)
        array[counter + 3]++;
}

void rowsColsSpansScoring(SPFiarGame *src, SPMiniMaxNode *node, int *array, int rows, int columns){
    int counter = 0;

    for (int i = 0; i<rows; i++) {

        for (int j = 0; j < SP_FIAR_GAME_SPAN; j++) {
            if (rows==SP_FIAR_GAME_N_ROWS)
                updateFirstSpanCounter(src, node, i, j, &counter);
            else
                updateFirstSpanCounter(src, node, j, i, &counter);
            }

        incrementCellPerSpan(counter, array);

        for (int j = 1; j < columns - SP_FIAR_GAME_SPAN + 1; j++) {
            if (rows==SP_FIAR_GAME_N_ROWS)
                updateSpanCounter(src, node, i,  j, &counter);
            else
                updateSpanCounterTranspose(src, node, j, i, &counter);

            incrementCellPerSpan(counter, array);
        }
        counter =0;
    }
}

void diagonalSpansScoring(SPFiarGame *src, SPMiniMaxNode *node, int *array){
    int counter = 0;
    //bottom-left to top-right (green arrows)
    for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS - SP_FIAR_GAME_SPAN + 1; i++) {
        for (int row = 0, col = i;  row < SP_FIAR_GAME_SPAN; row++, col++) {
            updateFirstSpanCounter(src, node, row, col, &counter);
        }
        incrementCellPerSpan(counter, array);

        for (int row = 1, col = i+1;  row+SP_FIAR_GAME_SPAN-1 < SP_FIAR_GAME_N_ROWS &&
                                      col+SP_FIAR_GAME_SPAN-1 < SP_FIAR_GAME_N_COLUMNS; row++, col++){
            updateDiagLTR(src,node,row,col,&counter);
            incrementCellPerSpan(counter, array);
        }
        counter = 0;
    }
    // left to top-right (red arrows)
    for (int i = 1; i < SP_FIAR_GAME_N_ROWS - SP_FIAR_GAME_SPAN + 1; i++) {
        for (int row = i, col = 0;  col < SP_FIAR_GAME_SPAN; row++, col++) {
            updateFirstSpanCounter(src, node, row, col, &counter);
        }
        incrementCellPerSpan(counter, array);

        for (int row = i+1, col = 1;  row+SP_FIAR_GAME_SPAN-1 < SP_FIAR_GAME_N_ROWS &&
                                      col+SP_FIAR_GAME_SPAN-1 < SP_FIAR_GAME_N_COLUMNS; row++, col++){
            updateDiagLTR(src,node,row,col,&counter);
            incrementCellPerSpan(counter, array);
        }
        counter = 0;
    }
    //bottom-right to top-left (green arrows)
    for (int i = SP_FIAR_GAME_N_COLUMNS-1; i >= SP_FIAR_GAME_SPAN - 1; i--) {
        for (int row = 0, col = i;  row < SP_FIAR_GAME_SPAN; row++, col--) {
            updateFirstSpanCounter(src, node, row, col, &counter);
        }
        incrementCellPerSpan(counter, array);

        for (int row = 1, col = i-1;  row+SP_FIAR_GAME_SPAN-1 < SP_FIAR_GAME_N_ROWS &&
                                      col >= SP_FIAR_GAME_SPAN-1 ; row++, col--){
            updateDiagRTL(src,node,row,col,&counter);
            incrementCellPerSpan(counter, array);
        }
        counter = 0;
    }
    // right to top-left (red arrows)
    for (int i = 1; i < SP_FIAR_GAME_N_ROWS - SP_FIAR_GAME_SPAN + 1; i++) {
        for (int row = i, col = SP_FIAR_GAME_N_COLUMNS-1;  col >= SP_FIAR_GAME_N_COLUMNS-SP_FIAR_GAME_SPAN; row++, col--) {
            updateFirstSpanCounter(src, node, row, col, &counter);
        }
        incrementCellPerSpan(counter, array);

        for (int row = i+1, col = SP_FIAR_GAME_N_COLUMNS-2;  row+SP_FIAR_GAME_SPAN-1 < SP_FIAR_GAME_N_ROWS; row++, col--){
            updateDiagRTL(src,node,row,col,&counter);
            incrementCellPerSpan(counter, array);
        }
        counter = 0;
    }
}

int scoringFunction(SPFiarGame *src, SPMiniMaxNode *node) {
    assert(src != NULL);
    char winner = spFiarCheckWinner(src);
    if (winner == node->player)
        return INT_MAX;
    else if (winner == getOtherPlayer(node->player))
        return INT_MIN;
    else if (winner == SP_FIAR_GAME_TIE_SYMBOL)
        return 0;
    int *array = (int*)malloc((2*(SP_FIAR_GAME_SPAN-1))*sizeof(int));
    assert(array!=NULL);
    for (int i = 0 ; i<2*(SP_FIAR_GAME_SPAN-1);i++)
        array[i] = 0;
    rowsColsSpansScoring(src, node, array, SP_FIAR_GAME_N_ROWS, SP_FIAR_GAME_N_COLUMNS);

    rowsColsSpansScoring(src, node, array, SP_FIAR_GAME_N_COLUMNS, SP_FIAR_GAME_N_ROWS);

    diagonalSpansScoring(src, node,  array);

    int result = 0;
    for (int i=0; i<2*(SP_FIAR_GAME_SPAN-1); i++)
        result += array[i]*VECTOR[i];

    return result;
}

char getOtherPlayer(char player){
    if (player != SP_FIAR_GAME_PLAYER_1_SYMBOL && player != SP_FIAR_GAME_PLAYER_2_SYMBOL)
        return SP_FIAR_GAME_EMPTY_ENTRY;
    if (player==SP_FIAR_GAME_PLAYER_1_SYMBOL)
        return SP_FIAR_GAME_PLAYER_2_SYMBOL;
    return SP_FIAR_GAME_PLAYER_1_SYMBOL;
}

int updateAlphaBeta(SPMiniMaxNode *root, unsigned int maxDepth, char totalRootPlayer){
    char winner = spFiarCheckWinner(root->game);

    if (totalRootPlayer== winner) {
        root->alpha = INT_MAX;
        root->beta = root->alpha;
        return 1;
    }
    else if (getOtherPlayer(totalRootPlayer) == winner) {
        root->alpha = INT_MIN;
        root->beta = root->alpha;
        return 1;
    }
    if (maxDepth == 1){
        SPMiniMaxNode *child;
        for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (copy==NULL)
                    return -2;
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, getOtherPlayer(root->player),
                                       i);
                    child->alpha = root->isMaxType ? scoringFunction(child->game, root) : scoringFunction(child->game, child);
                    child->beta = child->alpha;
                    if (root->isMaxType) {
                        if (root->alpha < child->beta ) {
                            root->alpha = child->beta;
                        }
                    } else {
                        if (root->beta > child->alpha) {
                            root->beta = child->alpha;
                        }
                    }
                    if (root->alpha >= root->beta)
                        return 1;
                }
            }
        }
        return 1;
    }
        SPMiniMaxNode *child;
        for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (copy==NULL)
                    return -2;
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, getOtherPlayer(root->player),
                                       i);
                    int successful = updateAlphaBeta(child, maxDepth - 1, totalRootPlayer);
                    if (successful==-2)
                        return -2;
                    if (root->isMaxType) {
                        if (root->alpha < child->beta) {
                            root->alpha = child->beta;
                        }
                    } else {
                        if (root->beta > child->alpha) {
                            root->beta = child->alpha;
                        }
                    }
                    if (root->alpha >= root->beta)
                        return 1;
                }
            }
        }
        return 1;
}

SPMiniMaxNode *getMove(SPMiniMaxNode *root, unsigned int maxDepth){
    if (root==NULL)
        return NULL;
    SPMiniMaxNode *child;
    SPMiniMaxNode *bestNode = root;
    if (maxDepth == 1) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (copy==NULL)
                    return NULL;
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, getOtherPlayer(root->player),
                                       i);
                    child->alpha = scoringFunction(child->game, root);
                    child->beta = child->alpha;
                    if (root->isMaxType) {
                        if (root->alpha < child->beta || bestNode==root) {
                            bestNode = child;
                            root->alpha = child->beta;
                        }
                    }
                    if (root->alpha >= root->beta)
                        return bestNode;
                }
            }
        }
        return bestNode;
    }
    else {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (copy==NULL)
                    return NULL;
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, getOtherPlayer(root->player),
                                       i);
                    int successful = updateAlphaBeta(child,maxDepth-1,root->player);
                    if (successful==-2)
                        return NULL;
                    if (root->alpha < child->beta || bestNode==root) {
                        bestNode = child;
                        root->alpha = child->beta;
                    }

                    if (root->alpha >= root->beta)
                        return bestNode;
                }
            }
        }
        return bestNode;
    }
}

