
#include "stdio.h"
#include "defs.h"

void printBitBoard(U64 bb){
    U64 one = 1ULL;
    for (int i = 0; i<BRD_SQ_NUM; i++){
        if ((one<<i) & bb){
            printf("  X");
        } 
        else{
            printf("  .");
        }
        if (i%8==7){
            printf("\n");
        }
    }
}   