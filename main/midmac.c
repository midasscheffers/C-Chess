#include "stdio.h"
#include "defs.h"

int main() {
    printf("\n");

    // seed move arrays
    AllInit();

    // print test
    for (int i = 0; i < 64 ; i++){
        printf("%3d", i);
        if (i%8==7) printf("\n");
    }
    printf("\n");
    int sq = G7;
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
    printf("\n");
    // add more pieces to the test bb
    SetBit(&testbb, E4);
    SetBit(&testbb, B7);
    printBitBoard(testbb);
    int sq64 = 0;
    while (testbb){
        sq64 = PopBit(&testbb);
        printf("Found Piece at: %d\n", sq64);
        printBitBoard(testbb);
    }
    return 0;
}