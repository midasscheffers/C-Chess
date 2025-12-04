
#include <stdio.h>
#include "stack/stack.h"
#include "defs.h"


int perf(S_BOARD *pos, int depth){
    if (depth == 0){
        return 1;
    }
    stack moves_in_pos = create_stack();
    generateMoves(pos);
    // PrintBoard(pos);
    // PrintMoves();
    for (int i = 0 ; i<MAX_POS_MOVES_ONE_POS; ++i){
        if (possible_moves[i] == NULL_MOVE) break;
        U32 m = possible_moves[i];
        // printf("Pushed move: %lx\n", m);
        push(&moves_in_pos, m);
    }
    U32 current_move;
    int total = 0;
    while ((current_move = pop(&moves_in_pos)) != STACK_EMPTY)
    {   
        // printf("Made move: %lx\n", current_move);
        MakeMove(current_move, pos);
        total += perf(pos, depth-1);
        UnDoMove(pos);
    }
    return total;   
}


int main(){
    AllInit();
    S_BOARD b[1];
    ResetBoard(b);
    int _ = LoadFen(START_FEN, b);
    printf("Perf test:\n");
    for (int i = 1; i<6; i++){
        printf("Perf ply %d: %d\n", i, perf(b, i));
    }
    
    return 0;
}