#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "unit_test_util.h"

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
    else if (src->gameBoard[row][col] != '\0') // it is the opponent!
        (*counter)--;
}

void updateSpanCounter(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row][col - 1] == node->player)
        (*counter)--;
    else if (src->gameBoard[row][col - 1] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row][col + SP_FIAR_GAME_SPAN - 1] == node->player)
        (*counter)++;
    else if (src->gameBoard[row][col + SP_FIAR_GAME_SPAN - 1] != '\0') // it is the opponent!
        (*counter)--;
}

void updateSpanCounterTranspose(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row -1][col] == node->player)
        (*counter)--;
    else if (src->gameBoard[row -1][col] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col ] == node->player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col ] != '\0') // it is the opponent!
        (*counter)--;
}

void updateDiagLTR(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row-1][col - 1] == node->player)
        (*counter)--;
    else if (src->gameBoard[row-1][col - 1] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col + SP_FIAR_GAME_SPAN - 1] == node->player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col + SP_FIAR_GAME_SPAN - 1] != '\0') // it is the opponent!
        (*counter)--;
}

void updateDiagRTL(SPFiarGame *src, SPMiniMaxNode *node, int row, int col, int *counter){
    if (src->gameBoard[row-1][col + 1] == node->player)
        (*counter)--;
    else if (src->gameBoard[row-1][col + 1] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col - SP_FIAR_GAME_SPAN + 1] == node->player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col - SP_FIAR_GAME_SPAN + 1] != '\0') // it is the opponent!
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
    else if (winner != '\0')
        return INT_MIN;
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

char changePlayer(char player){
    if (player != SP_FIAR_GAME_PLAYER_1_SYMBOL && player != SP_FIAR_GAME_PLAYER_2_SYMBOL)
        return '\0';
    if (player==SP_FIAR_GAME_PLAYER_1_SYMBOL)
        return SP_FIAR_GAME_PLAYER_2_SYMBOL;
    return SP_FIAR_GAME_PLAYER_1_SYMBOL;
}

void *updateAlphaBeta(SPMiniMaxNode *root, unsigned int maxDepth){
    char winner;
    if ((winner = spFiarCheckWinner(root->game)) != '\0') {
        root->alpha = scoringFunction(root->game,root);
        root->beta = root->alpha;
        return NULL;
    }
    if (maxDepth == 1){
        SPMiniMaxNode *child;
//        SPMiniMaxNode *bestNode = root;
        for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, changePlayer(root->player),
                                       i);
                    child->alpha = scoringFunction(child->game, child);
                    child->beta = child->alpha;
                    if (root->isMaxType) {
                        if (root->alpha < child->beta ) {
//                            bestNode = child;
                            root->alpha = child->beta;
                        }
                    } else {
                        if (root->beta > child->alpha) {
//                            bestNode = child;
                            root->beta = child->alpha;
                        }
                    }
                    if (root->alpha >= root->beta)
                        return NULL;
//                        return root;

                }
            }
        }
        return NULL;
    }
    while (root->alpha < root->beta){
        SPMiniMaxNode *child;
//        SPMiniMaxNode *currentBestNode = root;
//        SPMiniMaxNode *bestNode = root;
        for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                child = createNode(root->alpha, root->beta, 1-root->isMaxType, copy, changePlayer(root->player),i);
                updateAlphaBeta(child,maxDepth-1);
                if (root->isMaxType){
                    if (root->alpha < child->beta) {
                        root->alpha = child->beta;
//                        bestNode = currentBestNode;
                    }
                }
                else {
                    if (root->beta > child->alpha) {
                        root->beta = child->alpha;
//                        bestNode = currentBestNode;
                    }
                    
                }

                if (root->alpha >= root->beta)
                    return NULL;  
            }
            
        }
        return NULL;
    }

}

SPMiniMaxNode *getMove(SPMiniMaxNode *root, unsigned int maxDepth){
    if (root==NULL)
        return NULL;
    if (maxDepth == 1) {
        SPMiniMaxNode *child;
        SPMiniMaxNode *bestNode = root;
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, changePlayer(root->player),
                                       i);
                    child->alpha = scoringFunction(child->game, child);
                    child->beta = child->alpha;
                    if (root->isMaxType) {
                        if (root->alpha < child->beta) {
                            bestNode = child;
                            root->alpha = child->beta;
                        }
                    } else {
                        if (root->beta > child->alpha) {
                            bestNode = child;
                            root->beta = child->alpha;
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
        SPMiniMaxNode *child;
        SPMiniMaxNode *bestNode = root;
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            if (spFiarGameIsValidMove(root->game, i)) {
                SPFiarGame *copy = spFiarGameCopy(root->game);
                if (spFiarGameSetMove(copy, i) == SP_FIAR_GAME_SUCCESS) {
                    child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy, changePlayer(root->player),
                                       i);
                    updateAlphaBeta(child,maxDepth-1);
             
                    if (root->alpha < child->beta) {
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

