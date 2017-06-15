#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include "SPMiniMax.h"

#define HISTORYSIZE 20

int suggestMove(SPFiarGame *currentGame, unsigned int maxDepth) {
    if (currentGame == NULL)
        return -2;
    char winner = spFiarCheckWinner(currentGame);
    if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL || winner == SP_FIAR_GAME_PLAYER_2_SYMBOL
        || winner == SP_FIAR_GAME_TIE_SYMBOL) {
        printf("Error: the game is over\n");
        return 1;
    }
    int col = spMinimaxSuggestMove(currentGame, maxDepth);
    if (col == -2)
        return -2;
    printf("Suggested move: drop a disc to column %d\n", col + 1);
    return 1;
}


bool undoMove(SPFiarGame *currentGame) {
    int lastMove = currentGame->history->elements[0];
    SP_FIAR_GAME_MESSAGE msg;
    msg = spFiarGameUndoPrevMove(currentGame);
    if (msg == SP_FIAR_GAME_SUCCESS) {
        printf("Remove disc: remove computer's disc at column %d\n", lastMove + 1);
        lastMove = currentGame->history->elements[0];
        spFiarGameUndoPrevMove(currentGame);
        printf("Remove disc: remove user's disc at column %d\n", lastMove + 1);
        return 1;
    } else {
        printf("Error: cannot undo previous move!\n");
    }
    return 0;
}

void quit(SPFiarGame *currentGame) {
    printf("Exiting...\n");
    spFiarGameDestroy(currentGame);
    exit(0);
}

void restartGame(SPFiarGame *currentGame) {
    printf("Game restarted!\n");
    spFiarGameDestroy(currentGame);
}

bool processCommand(SPFiarGame *currentGame, SPCommand command, unsigned int maxDepth, char *winner) {
    if (!command.validArg) {
        printf("Error: invalid command\n");
        return 0;
    } else if (command.cmd == SP_QUIT) {
        quit(currentGame);
        return 1;
    } else if (command.cmd == SP_RESTART) {
        restartGame(currentGame);
        return 1;
    } else if (command.cmd == SP_SUGGEST_MOVE) {
        int successful = suggestMove(currentGame, maxDepth);
        if (successful == -2) {
            spFiarGameDestroy(currentGame);
            exit(1);
        }
        return 0;
    } else if (command.cmd == SP_ADD_DISC) {
        if (command.arg < 1 || command.arg > 7) {
            printf("Error: column number must be in range 1-7\n");
            return 0;
        }
        if (!spFiarGameIsValidMove(currentGame, command.arg - 1)) {
            printf("Error: column %d is full\n", command.arg);
            return 0;
        }
        spFiarGameSetMove(currentGame, command.arg - 1);
        winner[0] = spFiarCheckWinner(currentGame);
        return 1;
    } else if (command.cmd == SP_UNDO_MOVE) {
        return undoMove(currentGame);
    }
    return 0;
}

char playFIAR(SPFiarGame **game, bool initGame, unsigned int *level) {
    char levelChar[1024];
    int colOfComputer = 0;
    char str[1024];
    char winner[1];
    winner[0] = SP_FIAR_GAME_EMPTY_ENTRY;
    SPCommand command;
    while (winner[0] == SP_FIAR_GAME_EMPTY_ENTRY) {
        if (initGame == 1) {
            do {
                printf("Please enter the difficulty level between [1-7]:\n");
                scanf("%s", levelChar);
                if (!strcmp(levelChar, "quit"))
                    quit(*game);
                (*level) = (unsigned int) atoi(levelChar);
                if ((*level) < 1 || (*level) > 7) {
                    printf("Error: invalid level (should be between 1 to 7)\n");
                }
            } while ((*level) < 1 || (*level) > 7);
            (*game) = spFiarGameCreate(HISTORYSIZE);
            if (*game == NULL) {
                exit(1);
            }
        }
        spFiarGamePrintBoard(*game);
        printf("Please make the next move:\n");
        do {
            fflush(stdin);
            fgets(str, 1024, stdin);
            scanf("%[^\n]s", str);
            command = spParserPraseLine(str);
        } while (!processCommand(*game, command, (*level), winner));
        if (command.cmd == SP_ADD_DISC && winner[0] == SP_FIAR_GAME_EMPTY_ENTRY) {
            colOfComputer = computerMove(*game, (*level), winner);
            if (colOfComputer == -2) {
                spFiarGameDestroy(*game);
                exit(1);
            }
            printf("Computer move: add disc to column %d\n", colOfComputer + 1);
            initGame = 0;
        }
        if (command.cmd == SP_UNDO_MOVE)
            initGame = 0;
        if (command.cmd == SP_RESTART)
            initGame = 1;

    }
    spFiarGamePrintBoard(*game);
    return winner[0];

}

bool checkCommandAfterGameisOver(SPCommand command, SPFiarGame **currentGame) {
    if (!command.validArg) {
        printf("Error: invalid command\n");
        return 0;
    } else if (command.cmd == SP_QUIT) {
        quit(*currentGame);
        return 1;
    } else if (command.cmd == SP_RESTART) {
        restartGame(*currentGame);
        return 1;
    } else if (command.cmd == SP_UNDO_MOVE)
        return undoMove(*currentGame);
    printf("Error: the game is over\n");
    return 0;

}

SPCommand gameOver(SPFiarGame **game, char winner) {
    SPCommand command;
    if (winner == SP_FIAR_GAME_TIE_SYMBOL)
        printf("Game over: it’s a tie\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    else if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL)
        printf("Game over: you win\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    else if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL)
        printf("Game over: computer wins\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    char str[1024];

    do {
        fflush(stdin);
        fgets(str, 1024, stdin);
        scanf("%[^\n]s", str);
        command = spParserPraseLine(str);
    } while (!checkCommandAfterGameisOver(command, game));
    return command;
}

