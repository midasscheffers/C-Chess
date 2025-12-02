#include <stdio.h>
#include <time.h>
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
    
    // move gen
    generateMoves(board);
    printf("Generated moves:\n");
    PrintMoves();
    printf("\n");
    // random moves
    srand(time(NULL));
    for (int j = 0; j<10;++j){
        generateMoves(board);
        int i;
        for (i = 0; i<MAX_POS_MOVES_ONE_POS;++i){
            if (possible_moves[i] == NULL_MOVE) break;
        }
        int random_number = rand() % (i);
        printf("Choose %d\n", random_number);
        MakeMove(possible_moves[random_number], board);
    }
    printf("random pos:\n\n");
    // seed random
    
    PrintBoard(board);
    printf("\n");
    // BoardPrintBitBorads(board);
    generateMoves(board);
    PrintMoves();
    printf("\n");
    return 0;
}