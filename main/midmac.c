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
    int _ = LoadFen("rnbqkbnr/pppppppp/8/8/8/8/5PPP/RNBQKBNR w KQkq - 0 1", board);
    PrintBoard(board);
    printf("\n");

    // move gen
    generateMoves(board);
    printf("Generated moves:\n");
    for (int i = 0; i<MAX_POS_MOVES_ONE_POS;++i){
        if (possible_moves[i] == NULL_MOVE) break;
        unsigned int  start = possible_moves[i]&0b111111;
        unsigned int  target = (possible_moves[i]&0b111111000000)>>6;
        char s_r = 8-start/8 + '0';
        char s_f = start%8 + 'a';
        char t_r = 8-target/8 + '0';
        char t_f = target%8 + 'a';
        printf("Move: %c%c, %c%c\n", s_f, s_r, t_f, t_r);
    }

    printf("\n");
    return 0;
}