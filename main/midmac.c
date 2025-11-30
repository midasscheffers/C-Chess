#include <stdio.h>
#include "defs.h"

int main() {
    printf("\n");

    // seed move arrays
    AllInit();

    for (int i = 0; i<BRD_SQ_NUM; ++i){
        printf("%3d", i);
        if (i%8==7) printf("\n");
    }
    printf("\n");

    // set up board
    S_BOARD board[1];
    ResetBoard(board);
    int _ = LoadFen(START_FEN, board);
    PrintBoard(board);
    printf("\n");
    // BoardPrintBitBorads(board);

    generateMoves(board);
    printf("Generated moves:\n");
    for (int i = 0; i<MAX_POS_MOVES_ONE_POS;++i){
        if (possible_moves[i] == NULL_MOVE) break;
        unsigned int  start = possible_moves[i]&0b111111;
        unsigned int  target = (possible_moves[i]&0b111111000000)>>6;
        printf("Move: %d, %d\n", start, target);
    }

    printf("\n");
    return 0;
}