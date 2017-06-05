#include <stdio.h>
#include <stdlib.h>
#include "SPArrayList.h"

SPArrayList* spArrayListCreate(int maxSize){ //TODO what about initializing the elements and actualsize
    if (maxSize <= 0){
        return NULL;
    }
    SPArrayList* arr = (SPArrayList*)malloc(sizeof(SPArrayList));
    if (arr == NULL)
        return NULL;
    arr->maxSize = maxSize;
    arr->actualSize = 0;
    arr->elements = (int*)malloc(maxSize*sizeof(int));
    if (arr->elements == NULL)
        return NULL;
    return arr;
}

SPArrayList* spArrayListCopy(SPArrayList* src){
    SPArrayList* arr = malloc(src->maxSize*sizeof(int));
    if (arr == NULL)
        return NULL;
    for (int i=0 ; i<sizeof(src) ; i++){
        arr[i].
    }
}