

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
    for (int i = 0; i<BRD_SQ_NUM; i++){
        int x=i%8;
        int y = i/8;
        int dir[8][2] = {{-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1}};
        // for dir
        for(int d = 0; d<8; d++){
            int index = 0;
            int curr_dir[2] = {dir[d][0], dir[d][1]};
            for (index; index<7; index++){
                int dx = (index+1)*curr_dir[0];
                int dy = (index+1)*curr_dir[1];
                if (onBoard(x+dx, y+dy)){
                    int target = (x+dx)+8*(y+dy);
                    SlidingMovesOnSq[i][d][index] = target;
                }
                else{
                    break;
                }
            }
            for(index; index < 8; index++){
                SlidingMovesOnSq[i][d][index] = NO_SQ;
            }
        }
    }
}


void AllInit(){
    InitKnightMoves();
    InitSlidingMoves();
}