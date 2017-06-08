#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "unit_test_util.h"

const int VECTOR[2*(SP_FIAR_GAME_SPAN-1)] ={-5,-2,-1,1,2,5};

void rowsColsSpansScoring(SPFiarGame *src, SPMiniMaxNode node, int *array, int rows, int columns){
    int counter = 0;

    for (int i = 0; i<rows; i++) {

        for (int j = 0; j < SP_FIAR_GAME_SPAN; j++) {
            if (src->gameBoard[i][j] == node.player)
                counter++;
            else if (src->gameBoard[i][j] != '\0') // it is the opponent!
                counter--;
        }
        if (counter > 0)
            array[counter + 2]++;
        else if (counter < 0)
            array[counter + 3]++;

        for (int j = 1; j < columns - SP_FIAR_GAME_SPAN + 1; j++) {

            if (src->gameBoard[i][j - 1] == node.player)
                counter--;
            else if (src->gameBoard[i][j - 1] != '\0') // it is the opponent!
                counter++;

            if (src->gameBoard[i][j + SP_FIAR_GAME_SPAN - 1] == node.player)
                counter++;
            else if (src->gameBoard[i][j + SP_FIAR_GAME_SPAN - 1] != '\0') // it is the opponent!
                counter--;

            if (counter > 0)
                array[counter + 2]++;
            else if (counter < 0)
                array[counter + 3]++;
        }
    }
}

void diagonalSpansScoring(SPFiarGame *src, SPMiniMaxNode node, int *array, int rows, int columns){
    
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
}

