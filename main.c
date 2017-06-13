

#include "unit_test_util.h"

#include "SPFIARGame.h"

#include "SPMiniMax.h"

#include "SPMiniMaxNode.h"

//#include "SPBufferset.h"

#include <stdbool.h>

#include <limits.h>



#define HISTORY_SIZE 20

//******assumption - all the indexes given and returned from the function are 0-based (0-6)!!!!******



static bool spFiarGameTest1() {

    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);

    ASSERT_TRUE(res!=NULL);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);//add_disc 2

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);//add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);//add_disc 1

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);//add_disc 2

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);//add_disc 4

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 1);

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2

    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);//add_disc 7

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 1);

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);//add_disc 5

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);//add_disc 3

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);//add_disc 1

    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1

    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);

    spFiarGamePrintBoard(res);

    return true;

}



static bool spFiarGameTest2() {

    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);

    ASSERT_TRUE(res!=NULL);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 0);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1

    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 0);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1

    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);

    spFiarGamePrintBoard(res);

    return true;

}



static bool spFiarGameTest3() {

    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);

    ASSERT_TRUE(res!=NULL);

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 6);

    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add disc to column 7

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 3);

    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4

    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add_disc 7

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 1);

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2

    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 0);

    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1

    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6

    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 2);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3

    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);

    spFiarGamePrintBoard(res);

    return true;

}



int main() {

    //SP_BUFF_SET();

    RUN_TEST(spFiarGameTest1);

    RUN_TEST(spFiarGameTest2);

    RUN_TEST(spFiarGameTest3);

}
