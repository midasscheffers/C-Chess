#include "stdio.h"
#include "defs.h"

int main() {
    printf("\n");

    AllInit();

    for (int i = 0; i < 64 ; i++){
        printf("%3d", i);
        if (i%8==7) printf("\n");
    }
    printf("\n");
    int sq = B2;
    U64 testbb = 1ULL << sq;
    printBitBoard(testbb);
    printf("\n");
    printf("Knight moves on sq %d:\n", sq);
    for (int i = 0; i<8; i++){
        printf("%3d", KnightMovesOnSq[sq][i]);
    }
    printf("\n\n");
    printf("Sliding moves on sq %d:\n", sq);
    for (int d=0;d<8;d++){
        printf(" In dir %d:", d);
        for (int m=0; m<7;m++){
            printf("%3d", SlidingMovesOnSq[sq][d][m]);
        }
        printf("\n");
    }

    return 0;
}