
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"

#define HISTORYSIZE 20


int main(){

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
    bool restart=1;
    SPFiarGame *game = spFiarGameCreate(HISTORYSIZE);
    while (winner[0] == SP_FIAR_GAME_EMPTY_ENTRY){
        if(restart==1) {
            do {
                printf("Please enter the difficulty level between [1-7]:\n");
                scanf("%s", levelChar);
                level = (unsigned int) atoi(levelChar);
                if (level < 1 || level > 7)
                    printf("Error: invalid level (should be between 1 to 7)\n");
            } while (level < 1 || level > 7);
            game = spFiarGameCreate(HISTORYSIZE);
        }
            spFiarGamePrintBoard(game);
            printf("Please make the next move:\n");
            do {
                fflush(stdin);
                fgets(str, 1024, stdin);
                scanf("%[^\n]s", str);
                command = spParserPraseLine(str);
            } while (!proccesComand(game, command, level, &winner));
            if (command.cmd != SP_UNDO_MOVE && command.cmd != SP_RESTART && winner[0]==SP_FIAR_GAME_EMPTY_ENTRY) {
                colOfComputer = computerMove(game, level);
                printf("Computer move: add disc to column %d\n", colOfComputer);
                restart=0;
            }
            if(command.cmd==SP_UNDO_MOVE || command.cmd==SP_ADD_DISC)
                restart=0;
            if(command.cmd==SP_RESTART)
                restart=1;
    }
    spFiarGamePrintBoard(game);
    if(winner[0]==SP_FIAR_GAME_TIE_SYMBOL)
        printf("Game over: it’s a tie\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    else if(winner[0]==SP_FIAR_GAME_PLAYER_1_SYMBOL)
        printf("Game over: you win\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    else if(winner[0]==SP_FIAR_GAME_PLAYER_2_SYMBOL)
        printf("Game over: computer wins\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    free(levelChar);
    free(winner);
    return 0;
}
