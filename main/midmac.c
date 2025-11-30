#include <stdio.h>
#include "defs.h"

int main() {
    printf("\n");

    // seed move arrays
    AllInit();

    // print tests
    for (int i = 0; i < 64 ; i++){
        printf("%3d", i);
        if (i%8==7) printf("\n");
    }
    printf("\n");

    S_BOARD board[1];
    
    ResetBoard(board);

    int _ = LoadFen(START_FEN, board);

    PrintBoard(board);
    printf("\n");

    _ = LoadFen("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2", board);

    PrintBoard(board);
    printf("\n");

    _ = LoadFen("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2", board);

    PrintBoard(board);

    printf("\n");
    return 0;
}