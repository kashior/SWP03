#include <stdio.h>
#include <string.h>
#include "SPFIARParser.h"
#include "SPArrayList.h"
void add(int *i){
//    printf("printing i: %d\n", i);
    (*i)++;

}

int main() {

// tests
//    printf("%d\n",spParserIsInt("7"));
//    char string[1024];
//    fgets (string, 1024, stdin);
//    SPCommand com = spParserPraseLine(string);
//    printf("%d\n",com.cmd == SP_ADD_DISC);
//    printf("%d\n",com.arg);
//    printf("%d\n",com.validArg);
//
//    printf("%d\n",com.cmd == SP_INVALID_LINE);
    SPArrayList* sym=spArrayListCreate(20);
//    sym->elements[0]=3;
//    sym->elements[1]=4;
//    sym->elements[2]=5;
    spArrayListAddFirst(sym, 13);
    spArrayListAddFirst(sym, 23);
    spArrayListAddFirst(sym, 5);
    printf("%d\n", sym->elements[2]);
    printf("%d\n", sym->elements[7]);
//    spArrayListRemoveFirst(sym);
    spArrayListAddAt(sym, 15, 1);
    SPArrayList* syn=spArrayListCopy(sym);
    spArrayListRemoveLast(sym);
    printf("%d\n", spArrayListGetLast(sym));
    printf("%d\n", spArrayListGetFirst(sym));


    int d = 6;
    add(&d);

    printf("%d", d);



    return 0;
}

