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
    int sq = G4;
    printf("Knightmoveson sq %d:\n", sq);
    U64 testbb = 1ULL << sq;
    printBitBoard(testbb);
    printf("\n");
    for (int i = 0; i<8; i++){
        printf("%3d", KnightMovesOnSq[sq][i]);
    }
    printf("\n\n");

    return 0;
}