
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
    unsigned int level=0;
    char winner = playFIAR(&game,initGame,&level);
    SPCommand command;
    do {
        command=gameOver(&game, winner);
        playFIAR(&game, (command.cmd == SP_RESTART), &level);
    } while(command.cmd != SP_QUIT);
    return 0;

}
