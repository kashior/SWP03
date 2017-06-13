#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SPFIARParser.h"

bool spParserIsInt(const char* str){
    if (str[0] != 45 && (str[0] < 48 || str[0] > 57))
        return false;
    else if (str[0] == 45 && str[1]=='\0')
        return false;

    for(int i=1;str[i] != '\0';i++){
        if (str[i] < 48 || str[i] > 57){
            return false;
        }
    }
    return true;
}

SP_COMMAND getSPComand(char* token){
    if (strcmp(token, "undo_move") == 0)
    {
        return SP_UNDO_MOVE;
    }
    else if (strcmp(token, "add_disc") == 0)
    {
        return SP_ADD_DISC;

    }else if (strcmp(token, "suggest_move") == 0)
    {
        return SP_SUGGEST_MOVE;
    }else if (strcmp(token, "quit") == 0)
    {
        return SP_QUIT;
    }else if (strcmp(token, "restart") == 0)
    {
        return SP_RESTART;
    }
    else
    {
        return SP_INVALID_LINE;
    }
}

SPCommand spParserPraseLine(const char* str){ //TODO what if we get more then 2 tokens?
    char str2[1024];
    strcpy(str2, str);
    const char delimiter[15] = " \t\r\n";
    char* token = strtok(str2,delimiter);
    SPCommand result;
    result.cmd = getSPComand(token);

    token = strtok(NULL, delimiter);
    if (result.cmd == SP_INVALID_LINE){
        result.validArg = false;
    }
    else if (result.cmd != SP_ADD_DISC && token != '\0'){
        result.validArg = false;
    }
    else if (result.cmd == SP_ADD_DISC && token == '\0'){
        result.validArg = false;
    }
    else if (result.cmd != SP_ADD_DISC && token == '\0'){
        result.validArg = true;
    }
    else if (result.cmd == SP_ADD_DISC && token != '\0'){
        if (!spParserIsInt(token)){
            result.validArg = false;
        }
        else{
            result.arg = atoi(token);
            result.validArg = true;
        }
    }
    token = strtok(NULL, delimiter);
    if(token!='\0')
        result.validArg = false;

    return result;
}





