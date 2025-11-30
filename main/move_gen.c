

#include <stdio.h>
#include "defs.h"


// int possible_moves[MAX_POS_MOVES_ONE_POS];


void genaratePawnMoves(int *index, S_BOARD *board){
    
}



void genarateKnightMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ?  board->whiteBB : board->blackBB;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wN+offset];
    while (current_bb)
    {   
        sq64 = PopBit(&current_bb);
        for (int i = 0; i<8; i++){
            int target = KnightMovesOnSq[sq64][i];
            if (target == NO_SQ){
                break;
            }
            // still have to check if the given sq is occupied by friend piece
            if (SetMask[target] & friendBB){
                break;
            }
            U32 m = sq64 | ((unsigned)target<<6);
            possible_moves[*index] = m;
            *index += 1;
        }
    }
}





void generateMoves(S_BOARD *pos){
    int index = 0;
    // generate all possible moves
    genarateKnightMoves(&index, pos);
    // int sq64 = B2;
    // for (int i = 0; i<8; i++){
    //     int target = KnightMovesOnSq[sq64][i];
    //     if (target == NO_SQ){
    //         break;
    //     }
    //     // still have to check if the given sq is occupied by friend piece
    //     U32 m = (unsigned) sq64 | (target<<6);
    //     possible_moves[index] = m;
    //     index++;
    // }

    // set last move to Null so we know where to stop
    possible_moves[index] = NULL_MOVE;
}