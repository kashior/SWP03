//#include "unit_test_util.h"
//
//#include "SPFIARGame.h"
//
//#include "SPMiniMax.h"
//
//#include "SPMiniMaxNode.h"
//
//#include <stdbool.h>
//
//#include <limits.h>
//
//
//
//#define HISTORY_SIZE 20
//
//
//
//
//
//static bool spFiarGameSetMoveTest1() {
//
//    printf("\n\n***spFiarGameSetMoveTest1***\n\n");
//
//    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//    ASSERT_TRUE(res!=NULL);
//
//    int repeat = 2;
//
//    while (repeat-- > 0) {
//
//        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//
//            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//
//        }
//
//    }
//
//
//
//    for (int i = 0; i < 3; i++) {
//
//        ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//
//    }
//
//
//
//    spFiarGamePrintBoard(res);
//
//    printf("\n\nwinner: %c\n\n",spFiarCheckWinner(res));
//
//
//
//
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//
//
//    spFiarGamePrintBoard(res);
//
//    printf("\n\nwinner %c\n\n",spFiarCheckWinner(res));
//
//    spFiarGameDestroy(res);
//
//
//
//    return true;
//
//}
//
//
//
//static bool spFiarGameSetMoveTest2() {
//
//    printf("\n\n***spFiarGameSetMoveTest2***\n\n");
//
//    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//    ASSERT_TRUE(res!=NULL);
//
//
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS);
//
//
//
//    spFiarGamePrintBoard(res);
//
//    printf("\n\nwinner: %c",spFiarCheckWinner(res));
//
//    printf("\n\nscoreFunction result:%d\n\n",scoreFunction(res));
//
//    spFiarGameDestroy(res);
//
//
//
//    return true;
//
//}
//
//
//
//
//
//static bool spFiarSuggestMoveTest1() {
//
//    printf("\n\n***spFiarSuggestMoveTest1***\n\n");
//
//    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//    ASSERT_TRUE(res!=NULL);
//
//    int repeat = 2;
//
//    while (repeat-- > 0) {
//
//        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//
//            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//
//        }
//
//    }
//
//
//
//    for (int i = 0; i < 4; i++) {
//
//        ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//
//    }
//
//
//
//    spFiarGamePrintBoard(res);
//
//    printf("\nsuggest col: %d\n",spMinimaxSuggestMove(res,7));
//
//    spFiarGameDestroy(res);
//
//
//
//    return true;
//
//}
//
//
//
//static bool spFiarSuggestMoveTest2() {
//
//    printf("\n\n***spFiarSuggestMoveTest2***\n\n");
//
//    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//    ASSERT_TRUE(res!=NULL);
//
//    int repeat = 2;
//
//    while (repeat-- > 0) {
//
//        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
//
//            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
//
//        }
//
//    }
//
//
//
//    spFiarGamePrintBoard(res);
//
//    printf("\nsuggest col: %d\n",spMinimaxSuggestMove(res,7));
//
//    spFiarGameDestroy(res);
//
//
//
//    return true;
//
//}
//
//
//
//static bool spFiarSuggestMoveTest3() {
//
//    printf("\n\n***spFiarSuggestMoveTest3***\n\n");
//
//    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//    ASSERT_TRUE(res!=NULL);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);
//
//
//
//
//
//    spFiarGamePrintBoard(res);
//
//    printf("\nsuggest col: %d\n",spMinimaxSuggestMove(res,7));
//
//    spFiarGameDestroy(res);
//
//
//
//    return true;
//
//}
//
//
//
//static bool spFiarSuggestMoveTest4() {
//
//    printf("\n\n***spFiarSuggestMoveTest4***\n\n");
//
//    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//    ASSERT_TRUE(res!=NULL);
//
//    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);
//
//    spFiarGamePrintBoard(res);
//
//    printf("\n suggest column: %d **%c**\n",spMinimaxSuggestMove(res,2),res->currentPlayer);
//
//    return true;
//
//}
//
//
//
//
//
//
//
//int minimaxunittest() {
//
//    RUN_TEST(spFiarGameSetMoveTest1);
//
//    RUN_TEST(spFiarGameSetMoveTest2);
//
//    RUN_TEST(spFiarSuggestMoveTest1);
//
//    RUN_TEST(spFiarSuggestMoveTest2);
//
//    RUN_TEST(spFiarSuggestMoveTest3);
//
//    RUN_TEST(spFiarSuggestMoveTest4);
//
//
//
//}
//
//
