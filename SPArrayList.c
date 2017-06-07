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
    if (arr == NULL || src->elements==NULL)
        return NULL;
    arr->elements=(int*)malloc(src->maxSize*sizeof(int));
    for(int i=0; i<sizeof(src->elements)/sizeof(int); i++)
        arr->elements[i]=src->elements[i];
    arr->actualSize=src->actualSize;
    arr->maxSize=src->maxSize;
    return arr;
}
void spArrayListDestroy(SPArrayList* src)
{
    if(src!=NULL) {
        free(src->elements);
        free(src);
    }
}
SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src)
{
    SP_ARRAY_LIST_MESSAGE msg= SP_ARRAY_LIST_INVALID_ARGUMENT;
    if(src==NULL)
        return msg;
    else
    {
        src->elements={};
        src->actualSize=0;
        msg = SP_ARRAY_LIST_SUCCESS;
        return msg;
    }

}
SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index)
{
    if(src==NULL || index>src->actualSize || index<0)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if(src->actualSize==src->maxSize)
        return SP_ARRAY_LIST_FULL;
    src->actualSize++;
    for(int i=src->actualSize;i>index;i--)
        src->elements[i]=src->elements[i-1];
    src->elements[index]=elem;
    return SP_ARRAY_LIST_SUCCESS;
}
SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem)
{
    return spArrayListAddAt( src,  elem, 0);
}