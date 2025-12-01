

#include <stdio.h>
#include "defs.h"


void genaratePawnMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ?  board->whiteBB : board->blackBB;
    U64 enemBB = (board->toMove == WHITE) ?  board->blackBB : board->whiteBB;
    int dir_offset = (board->toMove == WHITE) ? 0 : 5;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wP+offset];
    while (current_bb)
    {   
        sq64 = PopBit(&current_bb);
        // check side dir
        int flank1 = SlidingMovesOnSq[sq64][0+dir_offset][0];
        int flank2 = SlidingMovesOnSq[sq64][2+dir_offset][0];
        if ((flank1 != NO_SQ) && (SetMask[flank1]&enemBB)){
            U32 m = sq64 | ((unsigned)flank1<<6);
            possible_moves[*index] = m;
            *index += 1;
        }
        if ((flank2 != NO_SQ) && (SetMask[flank2]&enemBB)){
            U32 m = sq64 | ((unsigned)flank2<<6);
            possible_moves[*index] = m;
            *index += 1;
        }
        // check front
        int front = SlidingMovesOnSq[sq64][1+dir_offset][0];
        int f_move_check = 0;
        if ((front != NO_SQ) && !(SetMask[front]&(friendBB|enemBB))){
            f_move_check = 1;
            U32 m = sq64 | ((unsigned)front<<6);
            possible_moves[*index] = m;
            *index += 1;
        }
        // check double move
        int two_front = SlidingMovesOnSq[sq64][1+dir_offset][1];
        int first_rank = (board->toMove == WHITE) ? RANK_7 : RANK_2;
        if (f_move_check && (sq64/8==first_rank) && (two_front != NO_SQ) && !(SetMask[two_front]&(friendBB|enemBB))){
            U32 m = sq64 | ((unsigned)two_front<<6);
            possible_moves[*index] = m;
            *index += 1;
        }
    }
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
                continue;
            }
            if (SetMask[target] & friendBB){
                continue;
            }
            U32 m = sq64 | ((unsigned)target<<6);
            possible_moves[*index] = m;
            *index += 1;
        }
    }
}


void genarateRookMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ?  board->whiteBB : board->blackBB;
    U64 enemBB = (board->toMove == WHITE) ?  board->blackBB : board->whiteBB;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wR+offset];
    while (current_bb)
    {   
        sq64 = PopBit(&current_bb);
        for(int d =0;d<8;++d){
            if (d%2==0) continue;
            for (int i = 0; i<7; i++){
                int target = SlidingMovesOnSq[sq64][d][i];
                if (target == NO_SQ){
                    break;
                }
                if (SetMask[target] & friendBB){
                    break;
                }
                U32 m = sq64 | ((unsigned)target<<6);
                possible_moves[*index] = m;
                *index += 1;
                if (SetMask[target] & enemBB){
                    break;
                }
            }
        }
    }
}


void genarateBishopMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ?  board->whiteBB : board->blackBB;
    U64 enemBB = (board->toMove == WHITE) ?  board->blackBB : board->whiteBB;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wB+offset];
    while (current_bb)
    {   
        sq64 = PopBit(&current_bb);
        for(int d =0;d<8;++d){
            if (d%2==1) continue;
            for (int i = 0; i<7; i++){
                int target = SlidingMovesOnSq[sq64][d][i];
                if (target == NO_SQ){
                    break;
                }
                if (SetMask[target] & friendBB){
                    break;
                }
                U32 m = sq64 | ((unsigned)target<<6);
                possible_moves[*index] = m;
                *index += 1;
                if (SetMask[target] & enemBB){
                    break;
                }
            }
        }
    }
}

void genarateQueenMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ?  board->whiteBB : board->blackBB;
    U64 enemBB = (board->toMove == WHITE) ?  board->blackBB : board->whiteBB;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wQ+offset];
    while (current_bb)
    {   
        sq64 = PopBit(&current_bb);
        for(int d =0;d<8;++d){
            for (int i = 0; i<7; i++){
                int target = SlidingMovesOnSq[sq64][d][i];
                if (target == NO_SQ){
                    break;
                }
                if (SetMask[target] & friendBB){
                    break;
                }
                U32 m = sq64 | ((unsigned)target<<6);
                possible_moves[*index] = m;
                *index += 1;
                if (SetMask[target] & enemBB){
                    break;
                }
            }
        }
    }
}

void genarateKingMoves(int *index, S_BOARD *board){
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ?  board->whiteBB : board->blackBB;
    U64 enemBB = (board->toMove == WHITE) ?  board->blackBB : board->whiteBB;
    int sq64 = 0;
    U64 current_bb = board->bitBoards[wK+offset];
    while (current_bb)
    {   
        sq64 = PopBit(&current_bb);
        for(int d =0;d<8;++d){
            int target = SlidingMovesOnSq[sq64][d][0];
            if (target == NO_SQ){
                continue;
            }
            if (SetMask[target] & friendBB){
                continue;
            }
            U32 m = sq64 | ((unsigned)target<<6);
            possible_moves[*index] = m;
            *index += 1;
            if (SetMask[target] & enemBB){
                continue;
            }
        }
    }
}


void generateMoves(S_BOARD *pos){
    //set global index into the posibble_move array
    int index = 0;

    // generate all possible moves
    // Knights
    genarateKnightMoves(&index, pos);
    //Pawns
    genaratePawnMoves(&index, pos);
    //Rooks
    genarateRookMoves(&index, pos);
    //Bishops
    genarateBishopMoves(&index, pos);
    //Queens
    genarateQueenMoves(&index, pos);
    //Kings
    genarateKingMoves(&index, pos);

    // set last move to Null so we know where to stop
    possible_moves[index] = NULL_MOVE;
}