#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"

SPFiarGame *spFiarGameCreate(int historySize) {
    if (historySize <= 0)
        return NULL;
    SPFiarGame *game = (SPFiarGame *) malloc(sizeof(SPFiarGame));
    if (game == NULL) {
        return NULL;
    }
    for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++)
        game->tops[i] = 0;
    game->history = spArrayListCreate(historySize);
    if (game->history == NULL)
        return NULL;
    game->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    return game;
}

SPFiarGame *spFiarGameCopy(SPFiarGame *src) {
    if (src == NULL)
        return NULL;
    SPFiarGame *copy = (SPFiarGame *) malloc(sizeof(SPFiarGame));
    if (copy == NULL)
        return NULL;
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
            copy->gameBoard[i][j] = src->gameBoard[i][j];
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
        copy->tops[i] = src->tops[i];
    }
    copy->currentPlayer = src->currentPlayer;
    copy->history = spArrayListCopy(src->history);
    if (copy->history == NULL)
        return NULL;
    copy->undoCounter = src->undoCounter;
    return copy;
}

void spFiarGameDestroy(SPFiarGame *src) {
    if (src != NULL) {
        free(src->history);
        free(src);
    }
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame *src, int col) {
    if (src == NULL || col < 0 || col > SP_FIAR_GAME_N_COLUMNS - 1)
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    if (src->tops[col] == SP_FIAR_GAME_N_ROWS)
        return SP_FIAR_GAME_INVALID_MOVE;
    src->gameBoard[src->tops[col]][col] = src->currentPlayer;
    src->tops[col]++;
    if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL)
        src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
    else
        src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    if (src->history->maxSize == src->history->actualSize)
        spArrayListRemoveLast(src->history);
    spArrayListAddFirst(src->history, col);
    src->undoCounter = 0;
    return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame *src, int col) {
    if (src == NULL || col < 0 || col > SP_FIAR_GAME_N_COLUMNS - 1)
        return false;
    if (src->tops[col] == SP_FIAR_GAME_N_ROWS)
        return false;
    return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame *src) {
    if (src == NULL)
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    if (src->undoCounter == src->history->maxSize || src->history->actualSize == 0)
        return SP_FIAR_GAME_NO_HISTORY;
    int col = spArrayListGetFirst(src->history);
    SP_ARRAY_LIST_MESSAGE msg = spArrayListRemoveFirst(src->history);
    if (msg == SP_ARRAY_LIST_EMPTY || msg == SP_ARRAY_LIST_INVALID_ARGUMENT)
        return SP_FIAR_GAME_NO_HISTORY;
    src->gameBoard[src->tops[col] - 1][col] = '\0';
    src->tops[col]--;
    src->undoCounter++;
    if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL)
        src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
    else
        src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    return SP_FIAR_GAME_SUCCESS;

}


char spFiarGameGetCurrentPlayer(SPFiarGame *src) {
    if (src == NULL)
        return SP_FIAR_GAME_EMPTY_ENTRY;
    return src->currentPlayer;
}

char checkSymbol(SPFiarGame *src, int row, int col, int *player1Counter, int *player2Counter) {
    if (src->gameBoard[row][col] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
        player2Counter = 0;
        player1Counter++;
    } else if (src->gameBoard[row][col] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
        (*player1Counter) = 0;
        (*player2Counter)++;
    } else {
        (*player1Counter) = 0;
        (*player2Counter) = 0;
    }
    if ((*player1Counter) == 4) {
        return SP_FIAR_GAME_PLAYER_1_SYMBOL;
    }
    if ((*player2Counter) == 4) {
        return SP_FIAR_GAME_PLAYER_2_SYMBOL;
    }
    return '\0';
}


char rowsColumnsWinner(SPFiarGame *src, int outer, int inner) {
    int player1Counter = 0;
    int player2Counter = 0;

    for (int i = 0; i < outer; i++) {
        for (int j = i; j < inner; j++) {
            char winner = checkSymbol(src, i, j, &player1Counter, &player2Counter);
            if (winner != '\0')
                return winner;
        }
    }
    return '\0';
}

char diagonalWinner(SPFiarGame *src) {
    int player1Counter = 0;
    int player2Counter = 0;

    // bottom-left to top-right
    for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS - SP_FIAR_GAME_SPAN + 1; i++) {
        for (int row = 0, col = i; row < SP_FIAR_GAME_N_ROWS && col < SP_FIAR_GAME_N_COLUMNS; row++, col++) {
            char winner = checkSymbol(src, row, col, &player1Counter, &player2Counter);
            if (winner != '\0')
                return winner;
        }
    }

    // left to top-right
    for (int i = 1; i < SP_FIAR_GAME_N_ROWS - SP_FIAR_GAME_SPAN + 1; i++) {
        for (int row = i, col = 0; row < SP_FIAR_GAME_N_ROWS && col < SP_FIAR_GAME_N_COLUMNS; row++, col++) {
            char winner = checkSymbol(src, row, col, &player1Counter, &player2Counter);
            if (winner != '\0')
                return winner;
        }
    }

    // bottom-right to top-left
    for (int i = SP_FIAR_GAME_N_COLUMNS-1; i >= SP_FIAR_GAME_SPAN - 1; i--) {
        for (int row = 0, col = i; row < SP_FIAR_GAME_N_ROWS && col >= 0; row++, col--) {
            char winner = checkSymbol(src, row, col, &player1Counter, &player2Counter);
            if (winner != '\0')
                return winner;
        }
    }

    // right to top-left
    for (int i = 1; i < SP_FIAR_GAME_N_ROWS - SP_FIAR_GAME_SPAN + 1; i++) {
        for (int row = i, col = SP_FIAR_GAME_N_COLUMNS-1; row < SP_FIAR_GAME_N_ROWS && col >=0; row++, col--) {
            char winner = checkSymbol(src, row, col, &player1Counter, &player2Counter);
            if (winner != '\0')
                return winner;
        }
    }

    return '\0';
}


char spFiarCheckWinner(SPFiarGame *src) {
    char winner = rowsColumnsWinner(src, SP_FIAR_GAME_N_ROWS, SP_FIAR_GAME_N_COLUMNS);
    if (winner != '\0')
        return winner;

    winner = rowsColumnsWinner(src, SP_FIAR_GAME_N_COLUMNS, SP_FIAR_GAME_N_ROWS);
    if (winner != '\0')
        return winner;

    winner = diagonalWinner(src);
    return winner;
}