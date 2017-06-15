

#include <string.h>
#include <printf.h>
#include "SPFIARGame.h"

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
        winner = playFIAR(&game, (command.cmd == SP_RESTART), &level);
    } while(command.cmd != SP_QUIT);
    return 0;

}
