

#include <stdio.h>
#include "defs.h"


// int possible_moves[MAX_POS_MOVES_ONE_POS];


void genaratePawnMoves(int *index, S_BOARD *board){
    
}



void genarateKnightMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wN+offset];
    printf("Generating Knight Moves:\n");
    printBitBoard(current_bb);
    while (current_bb)
    {
        sq64 = PopBit(&current_bb);
        for (int i = 0; i<8; i++){
            int target = KnightMovesOnSq[sq64][i];
            if (target == NO_SQ){
                break;
            }
            // still have to check if the given sq is occupied by friend piece
            int m = sq64 | (target<<5);
            possible_moves[*index] = m;
            *index++;
        }
    }
    printf("Found all knight moves.\n");
}





void generateMoves(S_BOARD *board){
    int index = 0;
    // generate all possible moves
    // genarateKnightMoves(&index, board);
    int sq64 = B2;
    for (int i = 0; i<8; i++){
            int target = KnightMovesOnSq[sq64][i];
            if (target == NO_SQ){
                break;
            }
            // still have to check if the given sq is occupied by friend piece
            M m = (unsigned) sq64 | (target<<6);
            possible_moves[index] = m;
            index++;
        }

    // set last move to Null so we know where to stop
    possible_moves[index] = NULL_MOVE;
}