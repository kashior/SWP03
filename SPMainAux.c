#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPFIARParser.h"

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

bool proccesComand(SPFiarGame* currentGame, SPCommand command, unsigned int maxDepth){
    if (!command.validArg) {
        printf("Error: invalid command\n");
        return 0;
    }
    else if (command.cmd == SP_QUIT) {
        quit(currentGame);
        return 1;
    }
    else if (command.cmd == SP_RESTART){
        restartGame(currentGame);
        return 1;
    }
    else if (command.cmd == SP_SUGGEST_MOVE){
        suggestMove(currentGame,maxDepth);
        return 1;
    }

}
