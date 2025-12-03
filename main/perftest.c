
#include <stdio.h>
#include "defs.h"
#include "stack/stack.h"


int perf(S_BOARD *b){
    stack move_stack = create_stack();
    generateMoves(b);
    for (int i =0 ; i<MAX_POS_MOVES_ONE_POS; ++i){
        if (possible_moves[i] == NULL_MOVE) break;
        push(&move_stack, possible_moves[i]);
    }
    int depth = 0;
    int max_depth = 3;
    U32 current_move;
    int total = 0;
    while ((current_move = pop(&move_stack)) != STACK_EMPTY)
    {   
        MakeMove(current_move, b);
        ++depth;
        if (depth >= max_depth){
            total ++;
            continue;
        }
        generateMoves(b);
        for (int i =0 ; i<MAX_POS_MOVES_ONE_POS; ++i){
            if (possible_moves[i] == NULL_MOVE) break;
            push(&move_stack, possible_moves[i]);
        }


    }
    return total;
}


int main(){
    S_BOARD b[1];
    printf("Perf: %d\n", perf(b));
    return 0;
}