
#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"

int main(){
    printf("Please enter the difficulty level between [1-7]:\n");
    unsigned int level;
    scanf("%d", &level);
    while (level<1 || level>7){
        printf("Error: invalid level (should be between 1 to 7\n");
        scanf("%d", &level);
    }
    printf("%d",level);

}
