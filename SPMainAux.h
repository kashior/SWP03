#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include "SPFIARGame.h"

/**
 * SPMainAux Summary:
 *
 *  In this module we store all the auxiliary functions and constants used by the main function.
 *
 * suggestMove           - Prints suggested move for the player
 * undoMove             - Undo two moves , if possible
 * quit          - Frees all memory resources associated with a game and exit
 * restartGame          - restart the game and start from the top
 * processCommand      - process a command given by the player and do what the player asks
 * playFIAR     - The actual game is played here
 * checkCommandAfterGameisOver       - does the same as processCommand but only after game is over
 * gameOver - check who wins after game is over and gives the player to act
 *
 */

/**
 * This function gets the source game and the level played insied the game and prints her recommendation
 * According to the miniMax algorithm
 * @param currentGame - the source game
 * @param maxDepth - the level of the game
 * @return
 * -2 if there's an error
 * 1 otherwise (and prints The col number that the function recommends (1-based))
 */

int suggestMove(SPFiarGame *currentGame, unsigned int maxDepth);

/**
 * Undo two moves , if possible
 * The function checks if undo is possible, and if so , it calls spFiarGameUndoPrevMove twice
 * In order to return the game to the last state - before computer and player turns.
 * @param currentGame - the source game
 */

void undoMove(SPFiarGame* currentGame);

/**
 * Frees all resources that are connected to the game and exit the program
 * @param currentGame - the source game
 */

void quit(SPFiarGame* currentGame);


/**
 * Restart the game and starts from choosing the difficulty level
 * Cleans all the data related to the last game and starts a new one
 * @param currentGame - the source game
 */
void restartGame(SPFiarGame* currentGame);

/**
 * The function gets a command , process it and performs the right action
 * There are commands that demand player change and there are commands that will leave the same player
 * That's why this function is boolean, and also if the command is invalid it should be false
 * @param currentGame - the source game
 * @param command - command typed by the user
 * @param maxDepth - the difficulty level
 * @param winner - the winner in the game
 * @return
 * true if the command processed will cause player change
 * false otherwise
 */

bool processCommand(SPFiarGame *currentGame, SPCommand command, unsigned int maxDepth, char *winner);

/**
 * The actual game happens in this function
 * It uses all the modules we built and run the game
 * @param game - the source game
 * @param initGame - flag for checking if game need to be initialized
 * @param level - the difficulty level
 * @return
 * SP_FIAR_GAME_PLAYER_1_SYMBOL - if player 1 won
 * SP_FIAR_GAME_PLAYER_2_SYMBOL - if player 2 won
 * SP_FIAR_GAME_TIE_SYMBOL - If the game is over and there's a tie
 * null otherwise
 */

char playFIAR(SPFiarGame** game,bool initGame, unsigned int* level);

/**
 * This function is similar the processCommand, the big difference is that
 * It cun process only 3 commands instead of 5, because it is called only when the game is over
 * @param command - the command entered by the user
 * @param currentGame - the source game
 * @return
 * true if the command is legit
 * false otherwise
 */

bool checkCommandAfterGameisOver(SPCommand command,SPFiarGame** currentGame );

/**
 * This function is being called when the game is over. either there's a winner or a tie.
 * The function asks from the player to either quit, restart or undo the last move
 * @param game - the source game
 * @param winner - the winner of the game (or a tie symbol)
 * @return
 * one of the SPCommand commands according to the player
 */

SPCommand gameOver(SPFiarGame** game, char winner);

#endif
