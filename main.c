#include "unit_test_util.h"
#include "SPFIARGame.h"
#include <stdbool.h>

#define HISTORY_SIZE 20

static bool spFiarGameValidMoveTest() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = SP_FIAR_GAME_N_ROWS;
    while (repeat-- > 0) {
        ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);

    }
    ASSERT_FALSE(spFiarGameIsValidMove(res, 2));
    ASSERT_TRUE(spFiarGameSetMove(res,2)==SP_FIAR_GAME_INVALID_MOVE);
    spFiarGamePrintBoard(res);
    spFiarGameDestroy(res);
    return true;
}

static bool spFiarGameUndoMoveTest2() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = 3;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }
    }
    repeat = 20;
    while (repeat-- > 0) {
        ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
    }
    ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_NO_HISTORY);
    spFiarGamePrintBoard(res);
    spFiarGameDestroy(res);
    return true;
}
static bool spFiarGameUndoMoveTest() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = 2;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }
    }
    repeat = 2;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
        }
    }
    spFiarGamePrintBoard(res);
    spFiarGameDestroy(res);
    return true;
}

static bool spFiarGameSetMoveTest() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = 2;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }
    }
    spFiarGamePrintBoard(res);
    spFiarGameDestroy(res);
    return true;
}

static bool spFIARGameBasicTest() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    spFiarGameDestroy(res);
    return true;
}

int main() {
//    RUN_TEST(spFIARGameBasicTest);
//    RUN_TEST(spFiarGameSetMoveTest);
//    RUN_TEST(spFiarGameUndoMoveTest);
//    RUN_TEST(spFiarGameUndoMoveTest2);
//    RUN_TEST(spFiarGameValidMoveTest);
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    for (int i = 0; i<4; i++) {
        spFiarGameSetMove(res, i);

    }
    for (int i = 0; i<4; i++) {
        spFiarGameSetMove(res, i);

    }
    for (int i = 1; i<5; i++) {
        spFiarGameSetMove(res, i);

    }
    for (int i = 2; i<4; i++) {
        spFiarGameSetMove(res, i);

    }
    spFiarGameSetMove(res, 3);


//    ASSERT_TRUE(res!=NULL);
//    int repeat = SP_FIAR_GAME_N_ROWS+1;
//    while (repeat-- > 0) {
//        ASSERT_TRUE(spFiarGameSetMove(res,(repeat % 2)) == SP_FIAR_GAME_SUCCESS);
//
//    }
//    ASSERT_FALSE(spFiarGameIsValidMove(res, 2));
//    ASSERT_TRUE(spFiarGameSetMove(res,2)==SP_FIAR_GAME_INVALID_MOVE);
    spFiarGamePrintBoard(res);
    char winner = spFiarCheckWinner(res);
    spFiarGameDestroy(res);
    return 0;
}
