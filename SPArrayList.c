#include <stdio.h>
#include <stdlib.h>
#include "SPArrayList.h"

SPArrayList *spArrayListCreate(int maxSize) {
    if (maxSize <= 0) {
        return NULL;
    }
    SPArrayList *arr = (SPArrayList *) malloc(sizeof(SPArrayList));
    if (arr == NULL)
        return NULL;
    arr->maxSize = maxSize;
    arr->actualSize = 0;
    arr->elements = (int *) malloc(maxSize * sizeof(int));
    if (arr->elements == NULL) {
        free(arr);
        printf("Error: spArrayListCreate has failed");
        exit(1);
    }


    return arr;
}

SPArrayList *spArrayListCopy(SPArrayList *src) {
    SPArrayList *arr = (SPArrayList *) malloc(src->maxSize * sizeof(int));
    if (arr == NULL || src->elements == NULL){
        printf("Error: spArrayListCopy has failed");
        exit(1);
    }
    arr->elements = (int *) malloc(src->maxSize * sizeof(int));
    if (arr->elements == NULL) {
        free(arr);
            printf("Error: spArrayListCopy has failed");
            exit(1);
    }
    for (int i = 0; i < src->actualSize; i++)
        arr->elements[i] = src->elements[i];
    arr->actualSize = src->actualSize;
    arr->maxSize = src->maxSize;
    return arr;
}

void spArrayListDestroy(SPArrayList *src) {
    if (src != NULL) {
        free(src->elements);
        free(src);
    }
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList *src) {
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    else {
        free(src->elements);
        src->elements = (int *) malloc(src->maxSize * sizeof(int));
        if(src->elements==NULL)
        {
            printf("Error: spArrayListClear has failed");
            exit(1);
        }
        src->actualSize = 0;
        return SP_ARRAY_LIST_SUCCESS;
    }

}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList *src, int elem, int index) {
    if (src == NULL || index > src->actualSize || index < 0)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if (src->actualSize == src->maxSize)
        return SP_ARRAY_LIST_FULL;
    for (int i = src->actualSize; i > index; i--)
        src->elements[i] = src->elements[i - 1];
    src->elements[index] = elem;
    src->actualSize++;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList *src, int elem) {
    return spArrayListAddAt(src, elem, 0);

}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList *src, int elem) {
    return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList *src, int index) {
    if (src == NULL || index > src->actualSize || index < 0)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if (src->actualSize == 0)
        return SP_ARRAY_LIST_EMPTY;
    for (int i = index; i < src->actualSize - 1; i++)
        src->elements[i] = src->elements[i + 1];
    src->elements[src->actualSize - 1] = 0;
    src->actualSize--;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList *src) {
    return spArrayListRemoveAt(src, 0);

}


SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList *src) {
    return spArrayListRemoveAt(src, src->actualSize - 1);
}

int spArrayListGetAt(SPArrayList *src, int index) {
    if (src == NULL || index >= src->actualSize || index < 0)
        return -1;
    if (src->actualSize == 0)
        return -1;
    return src->elements[index];
}

int spArrayListGetFirst(SPArrayList *src) {
    return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList *src) {
    return spArrayListGetAt(src, src->actualSize - 1);
}

int spArrayListMaxCapacity(SPArrayList *src) {
    if (src == NULL)
        return -1;
    return src->maxSize;
}

int spArrayListSize(SPArrayList *src) {
    if (src == NULL)
        return -1;
    return src->actualSize;
}

bool spArrayListIsFull(SPArrayList *src) {
    if (src == NULL)
        return false;
    return src->actualSize == src->maxSize;
}

bool spArrayListIsEmpty(SPArrayList *src) {
    if (src == NULL)
        return false;
    return src->actualSize == 0;
}
