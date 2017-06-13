#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.c"
#include "SPFIARGame.c"
#include "SPMiniMax.h"

void suggestMove(SPFiarGame* currentGame, unsigned int maxDepth){
    if (currentGame==NULL){
        printf("Error: suggestMove got a NULL game\n");
        return;
    }
    char winner = spFiarCheckWinner(currentGame);
    if (winner==SP_FIAR_GAME_PLAYER_1_SYMBOL || winner == SP_FIAR_GAME_PLAYER_2_SYMBOL
            || winner == SP_FIAR_GAME_TIE_SYMBOL){
        printf("Error: the game is over\n");
        return;
    }
    int col = spMinimaxSuggestMove(currentGame,maxDepth);
    if (col < 0 || col > SP_FIAR_GAME_N_COLUMNS-1){
        printf("Error: spMinimaxSuggestMove() returned invalid output\n");
        return;
    }
    printf("Suggested move: drop a disc to column %d\n", col+1);
}

void undoMove(SPFiarGame* currentGame){

}

void addDisc(SPFiarGame* currentGame, int col);

void quit(SPFiarGame* currentGame);

void restartGame(SPFiarGame* currentGame);