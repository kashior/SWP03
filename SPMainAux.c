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
    int lastMove=currentGame->history->elements[0];
    SP_FIAR_GAME_MESSAGE msg;
    msg=spFiarGameUndoPrevMove(currentGame);
    if(msg==SP_FIAR_GAME_SUCCESS) {
        printf("Remove disc: remove computer's disc at column %d\n", lastMove+1);
        lastMove = currentGame->history->elements[0];
        spFiarGameUndoPrevMove(currentGame);
        printf("Remove disc: remove user's disc at column %d\n", lastMove+1);
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

bool proccesComand(SPFiarGame* currentGame, SPCommand command, unsigned int maxDepth,char* winner){
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
    else if (command.cmd==SP_ADD_DISC){
        if(command.arg<1 || command.arg>7){
            printf("Error: column number must be in range 1-7\n");
            return 0;
            }
        if ( !spFiarGameIsValidMove(currentGame,command.arg-1)) {
           printf("Error: column %d is full\n",command.arg);
           return 0;
        }
        spFiarGameSetMove(currentGame,command.arg-1);
        winner[0]=spFiarCheckWinner(currentGame);
        return 1;
    }
    else if(command.cmd == SP_UNDO_MOVE){
        return undoMove(currentGame);
    }
    return 0;
}

 char playFIAR(SPFiarGame** game,bool initGame){
     char* levelChar=malloc(1024);
     if(levelChar==NULL)
     {
         printf("Error: main has failed");
         exit(1);
     }
     unsigned int level=0;
     int colOfComputer=0;
     char str[1024];
     char *winner =malloc(sizeof(char));
     if(winner==NULL)
     {
         printf("Error: main has failed");
         exit(1);
     }
     winner[0]=SP_FIAR_GAME_EMPTY_ENTRY;
     SPCommand command;

     while (winner[0] == SP_FIAR_GAME_EMPTY_ENTRY){
         if(initGame==1) {
             do {
                 printf("Please enter the difficulty level between [1-7]:\n");
                 scanf("%s", levelChar);
                 level = (unsigned int) atoi(levelChar);
                 if (level < 1 || level > 7)
                     printf("Error: invalid level (should be between 1 to 7)\n");
             } while (level < 1 || level > 7);
             (*game) = spFiarGameCreate(HISTORYSIZE);
         }
         spFiarGamePrintBoard(*game);
         printf("Please make the next move:\n");
         do {
             fflush(stdin);
             fgets(str, 1024, stdin);
             scanf("%[^\n]s", str);
             command = spParserPraseLine(str);
         } while (!proccesComand(*game, command, level, winner));
         if (command.cmd == SP_ADD_DISC && winner[0]==SP_FIAR_GAME_EMPTY_ENTRY) {
             colOfComputer = computerMove(*game, level,winner);
             printf("Computer move: add disc to column %d\n", colOfComputer+1);
             initGame=0;
         }
         if(command.cmd==SP_UNDO_MOVE )
             initGame=0;
         if(command.cmd==SP_RESTART)
             initGame=1;
     }
     free(levelChar);
     char theWinner=winner[0];
     free(winner);
     spFiarGamePrintBoard(*game);
     return theWinner;
 }
bool  checkCommandAfterGameisOver(SPCommand command,SPFiarGame** currentGame ){
    if (!command.validArg) {
        printf("Error: invalid command\n");
        return 0;
    }
    else if (command.cmd == SP_QUIT) {
        quit(*currentGame);
        return 1;
    }
    else if (command.cmd == SP_RESTART){
        restartGame(*currentGame);
        return 1;
    }
    else if(command.cmd == SP_UNDO_MOVE)
        return undoMove(*currentGame);
    printf("Error: the game is over\n");
    return 0;


}