
#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"

#define HISTORYSIZE 20


int main(){
    char *levelChar;
    int level;
    do {
        printf("Please enter the difficulty level between [1-7]:\n");
        scanf("%s", levelChar);
        level = atoi(levelChar);
        if (level<1 || level>7)
            printf("Error: invalid level (should be between 1 to 7)\n");
    } while (level<1 || level>7);
    SPFiarGame *game = spFiarGameCreate(HISTORYSIZE);
    char winner = SP_FIAR_GAME_EMPTY_ENTRY;
    SPCommand command;
    char* str;
    while (winner == SP_FIAR_GAME_EMPTY_ENTRY){
        spFiarGamePrintBoard(game);
        printf("Please make the next move:\n");
        fgets(str, 1024,stdin);
        command = spParserPraseLine(str);


    }



}
