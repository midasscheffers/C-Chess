

#include "stdio.h"
#include "defs.h"


int onBoard(int x, int y){
    if (x<0 || x>7 || y<0 || y>7){
        return FALSE;
    }
    return TRUE;
}


// precalcualte knight moves
int KnightMovesOnSq[BRD_SQ_NUM][8];

void InitKnightMoves(){

    for (int i = 0; i<BRD_SQ_NUM; i++){
        int x=i%8;
        int y = i/8;
        int index = -1;
        for (int j=-2; j<3; j++){
            for (int k=-2; k<3; k++){
                if (abs(k)!=abs(j) && k!=0 && j!=0){
                    if (onBoard(x+k, y+j)){
                        index+=1;
                        int target = (x+k)+8*(y+j);
                        KnightMovesOnSq[i][index] = target;
                    }
                }
            }
        }
        for(index++; index < 8; index++){
             KnightMovesOnSq[i][index] = NO_SQ;
        }
    }
}


// precalcualte sliding moves
int SlidingMovesOnSq[BRD_SQ_NUM][8][7];

void InitSlidingMoves(){
    
}


void AllInit(){
    InitKnightMoves();
    InitSlidingMoves();
}