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
    int i;
    for (i = 0; i<MAX_POS_MOVES_ONE_POS;++i){
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
    printf("random pos:\n");
    // seed random
    
    PrintBoard(board);
    // BoardPrintBitBorads(board);
    generateMoves(board);
    for (i = 0; i<MAX_POS_MOVES_ONE_POS;++i){
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