#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "unit_test_util.h"

const int VECTOR[2*(SP_FIAR_GAME_SPAN-1)] ={-5,-2,-1,1,2,5};

void updateFirstSpanCounter(SPFiarGame *src, SPMiniMaxNode node, int row, int col, int *counter){
    if (src->gameBoard[row][col] == node.player)
        (*counter)++;
    else if (src->gameBoard[row][col] != '\0') // it is the opponent!
        (*counter)--;
}

void updateSpanCounter(SPFiarGame *src, SPMiniMaxNode node, int row, int col, int *counter){
    if (src->gameBoard[row][col - 1] == node.player)
        (*counter)--;
    else if (src->gameBoard[row][col - 1] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row][col + SP_FIAR_GAME_SPAN - 1] == node.player)
        (*counter)++;
    else if (src->gameBoard[row][col + SP_FIAR_GAME_SPAN - 1] != '\0') // it is the opponent!
        (*counter)--;
}

void updateDiagLTR(SPFiarGame *src, SPMiniMaxNode node, int row, int col, int *counter){
    if (src->gameBoard[row-1][col - 1] == node.player)
        (*counter)--;
    else if (src->gameBoard[row-1][col - 1] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col + SP_FIAR_GAME_SPAN - 1] == node.player)
        (*counter)++;
    else if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col + SP_FIAR_GAME_SPAN - 1] != '\0') // it is the opponent!
        (*counter)--;
}

void updateDiagRTL(SPFiarGame *src, SPMiniMaxNode node, int row, int col, int *counter){
    if (src->gameBoard[row-1][col + 1] == node.player)
        (*counter)--;
    else if (src->gameBoard[row-1][col + 1] != '\0') // it is the opponent!
        (*counter)++;

    if (src->gameBoard[row+ SP_FIAR_GAME_SPAN - 1][col - SP_FIAR_GAME_SPAN + 1] == node.player)
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

void rowsColsSpansScoring(SPFiarGame *src, SPMiniMaxNode node, int *array, int rows, int columns){
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
                updateSpanCounter(src, node, j,  i, &counter);

            incrementCellPerSpan(counter, array);
        }
    }
}

void diagonalSpansScoring(SPFiarGame *src, SPMiniMaxNode node, int *array){
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
    }

}

int scoringFunction(SPFiarGame *src, SPMiniMaxNode node) {
    assert(src != NULL);
    char winner = spFiarCheckWinner(src);
    if (winner == node.player)
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

