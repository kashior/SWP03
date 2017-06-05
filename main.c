#include <stdio.h>
#include <string.h>
#include "SPFIARParser.h"

int main() {

// tests
//    printf("%d\n",spParserIsInt("7"));
    char string[1024];
    fgets (string, 1024, stdin);
    SPCommand com = spParserPraseLine(string);
    printf("%d\n",com.cmd == SP_ADD_DISC);
    printf("%d\n",com.arg);
    printf("%d\n",com.validArg);

    printf("%d\n",com.cmd == SP_INVALID_LINE);






    return 0;
}