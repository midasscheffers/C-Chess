#include "stdio.h"
#include "defs.h"

int main() {

    AllInit();

    for (int i = 0; i < 64 ; i++){
        printf("%3d", i);
        if (i%8==7) printf("\n");
    }

    int num = 2;
    int nuts = 4;

    ASSERT(num==nuts);

    U64 testbb = 1ULL << E4;
    printBitBoard(testbb);

    return 0;
}