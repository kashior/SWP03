#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"

/**
 * SPMiniMaxNode summary:
 *
 * MinMax algorithm calculations
 *
 * scoringFunction          - return the score of the current game
 * createNode               - Creates a SPMiniMaxNode representing a move in the algorithm.
 * updateScoreOfRoot         - update the alpha or beta of root according to it's type - max or min
 * updateAlphaBeta          - recursively update the alpha and beta values of the nodes
 *                             in the subtree of the current node
 * getMove                  - returns the best move for the player according to the algorithm
 *
 * getOtherPlayer          - given a player, returns the char representing the other one
 */
typedef struct sp_minimax_node {
    int alpha;
    int beta;
    bool isMaxType; // flag helps determine if  this node is a max or min node
    SPFiarGame *game; // copy of the current game state
    char player; // the player who has to play next
    int move; // the column representing the move made by this node
} SPMiniMaxNode;

/**
 *	return the score of the current game according to the player given to it as a node argument
 *	@param currentGame - the current game state
 *	@param node - a MiniMax node representing the node the function should calculate the score
 *	according to
 *	@return
 *	the score of the game
 */
int scoringFunction(SPFiarGame *currentGame, SPMiniMaxNode *node);

/**
 * Creates a SPMiniMaxNode representing a move in the algorithm
 * @param alpha
 * @param beta
 * @param isMaxType - flag helps determine if  this node is a max or min node
 * @param copyOfGame - copy of the current game state
 * @param player - the player who has to play next
 * @param move - the column representing the move made by this node
 * @return
 * a pointer to the new node
 */
SPMiniMaxNode *createNode(int alpha, int beta, bool isMaxType, SPFiarGame *copyOfGame, char player, int move);

/**
 * update the alpha or beta of root according to it's type, max or min, and according to
 * the child's value if it improves the root's state
 * @param root - root node of the current subtree
 * @param child - child of the current subtree root
 */
void updateScoreOfRoot(SPMiniMaxNode *root, SPMiniMaxNode *child);

/**
 *  recursively update the alpha and beta values of the nodes
 *  in the subtree of the current node according to the MinMax algorithm
 *  and the scoringFunction
 * @param root - the current subtree root node
 * @param depth - the depth the algorithm should dive in the recursion
 * @param totalRootPlayer - the identity of the player who asked for a move suggestion
 * @return
 * 1 if everything is ok, and -2 if one of the pointer was NULL and the function could not
 * complete the calculation
 */
int updateAlphaBeta(SPMiniMaxNode *root, unsigned int depth, char totalRootPlayer);

/**
 * returns the best move for the current game using updateAlphaBeta and choosing the
 * node(representing move) with the biggest beta if the maxDepth > 1
 * using directly the scoringFunction for every possible move the player can make if
 * maxDepth = 1
 *
 * @param root - the current root node
 * @param maxDepth the depth the algorithm should dive in the recursion
 * @return
 * a node representing the move the player should make
 */
SPMiniMaxNode *getMove(SPMiniMaxNode *root, unsigned int maxDepth);

/**
 * given a player, returns the char representing the other one
 * @param player
 * @return
 * the other player
 */
char getOtherPlayer(char player);


#endif
