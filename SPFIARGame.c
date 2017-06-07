#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"

SPFiarGame* spFiarGameCreate(int historySize){
    if (historySize<= 0)
        return NULL;
    SPFiarGame* game = (SPFiarGame*)malloc(sizeof(SPFiarGame));
    if (game==NULL){
        return NULL;
    }
    game->history = spArrayListCreate(historySize);
    if (game->history ==NULL)
        return NULL;
    game->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    return game;
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src){
    if (src ==NULL)
        return NULL;
    SPFiarGame* copy = (SPFiarGame*)malloc(sizeof(SPFiarGame));
    if (copy ==NULL)
        return NULL;
    for (int i = 0 ; i< SP_FIAR_GAME_N_ROWS; i++){
        for (int j = 0; j<SP_FIAR_GAME_N_COLUMNS; j++){
            copy->gameBoard[i][j] = src->gameBoard[i][j];
        }
    }
    for (int i = 0 ; i< SP_FIAR_GAME_N_COLUMNS; i++){
        copy->tops[i] = src->tops[i];
    }
    copy->currentPlayer = src->currentPlayer;
    copy->history = spArrayListCopy(src->history);
    if (copy->history == NULL)
        return NULL;
    return copy;
}

void spFiarGameDestroy(SPFiarGame* src){
    if (src != NULL){
        free(src->history);
        free(src);
    }
}
