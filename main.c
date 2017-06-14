
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


    SPFiarGame *game ;
    bool initGame=1;
    char winner = playFIAR(&game,initGame);
//    while (winner[0] == SP_FIAR_GAME_EMPTY_ENTRY){
//        if(initGame==1) {
//            do {
//                printf("Please enter the difficulty level between [1-7]:\n");
//                scanf("%s", levelChar);
//                level = (unsigned int) atoi(levelChar);
//                if (level < 1 || level > 7)
//                    printf("Error: invalid level (should be between 1 to 7)\n");
//            } while (level < 1 || level > 7);
//            game = spFiarGameCreate(HISTORYSIZE);
//        }
//            spFiarGamePrintBoard(game);
//            printf("Please make the next move:\n");
//            do {
//                fflush(stdin);
//                fgets(str, 1024, stdin);
//                scanf("%[^\n]s", str);
//                command = spParserPraseLine(str);
//            } while (!proccesComand(game, command, level, winner));
//            if (command.cmd == SP_ADD_DISC && winner[0]==SP_FIAR_GAME_EMPTY_ENTRY) {
//                colOfComputer = computerMove(game, level,winner);
//                printf("Computer move: add disc to column %d\n", colOfComputer+1);
//                initGame=0;
//            }
//            if(command.cmd==SP_UNDO_MOVE )
//                initGame=0;
//            if(command.cmd==SP_RESTART)
//                initGame=1;
//    }

    if(winner==SP_FIAR_GAME_TIE_SYMBOL)
        printf("Game over: it’s a tie\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    else if(winner==SP_FIAR_GAME_PLAYER_1_SYMBOL)
        printf("Game over: you win\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    else if(winner==SP_FIAR_GAME_PLAYER_2_SYMBOL)
        printf("Game over: computer wins\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    char str[1024];
    SPCommand command;
    do {
        fflush(stdin);
        fgets(str, 1024, stdin);
        scanf("%[^\n]s", str);
        command = spParserPraseLine(str);
    }while(!checkCommandAfterGameisOver(command,&game));
    playFIAR(&game,(command.cmd==SP_RESTART));

    return 0;
}
