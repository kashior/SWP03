#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPFIARParser.h"

#define HISTORYSIZE 20

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

bool undoMove(SPFiarGame* currentGame){
    int x=currentGame->history->elements[0];
    SP_FIAR_GAME_MESSAGE msg;
    msg=spFiarGameUndoPrevMove(currentGame);
    if(msg==SP_FIAR_GAME_SUCCESS) {
        printf("Remove disc: remove computer's disc at column %d\n", x);
        x = currentGame->history->elements[0];
        spFiarGameUndoPrevMove(currentGame);
        printf("Remove disc: remove user's disc at column %d\n", x);
        return 1;
    }
    else{
        printf("Error: cannot undo previous move!\n");
    }
    return 0;
}


void quit(SPFiarGame* currentGame){
    printf("Exiting...\n");
    spFiarGameDestroy(currentGame);
    exit(0);
}

void restartGame(SPFiarGame* currentGame){
    printf("Game restarted!\n");
    spFiarGameDestroy(currentGame);
}

bool proccesComand(SPFiarGame* currentGame, SPCommand command, unsigned int maxDepth,char** winner){
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
        return 0;
    }
    else if (command.cmd==SP_ADD_DISC){  //TODO what if NULL?
        if(command.arg<1 || command.arg>7){
            printf("Error: column number must be in range 1-7\n");
            return 0;
            }
        if ( !spFiarGameIsValidMove(currentGame,command.arg-1)) {
           printf("Error: column %d is full\n",command.arg);
           return 0;
        }
        spFiarGameSetMove(currentGame,command.arg-1);
        char symbol=(spFiarCheckWinner(currentGame));
        (*winner)[0] = symbol;
        return 1;
    }
    else if(command.cmd == SP_UNDO_MOVE){
        if(undoMove(currentGame))
          return 1;
        return 0;
    }
    return 0;
}

