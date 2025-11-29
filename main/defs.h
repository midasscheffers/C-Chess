

#ifndef DEFS_H
#define DEFS_H

// include the sdt lib and basic assert functionality
#include "stdlib.h"

// toggle debug mode
#define DEGUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) {\
printf("%s - Failed", #n);\
printf("On %s ", __DATE__);\
printf("At %s ", __TIME__);\
printf("In File %s ", __FILE__);\
printf("At Line %d\n", __LINE__);\
exit(1);}
#endif

// make u64 type
typedef unsigned long long U64;

#define NAME "MidMec 0.01"
#define BRD_SQ_NUM 64

#define MAX_POS_MOVES 4092

enum {EMPTY, wK, wP, wN, wB, wR, wQ, bK, bP, bN, bB, bR, bQ}; // 0 EMPTY 1-6 White 7-12 Black
enum {NONE, WHITE, BLACK, BOTH};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};

enum{
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1, NO_SQ
};


enum {WKCA = 8, WQCA = 4, BKCA=2, BQCA=1};

enum {FALSE, TRUE};


typedef struct {
    int move;
    int castlePer;
    int enSq;
    int fiftyMove;
    U64 posKey;
} S_UNDO;

typedef struct
{
    U64 bitBoards[13];
    int pList[13][10];
    int epSq;
    int castlePerm;
    int toMove;
    int fiftyMove;
    int ply;
    int hisPly;

    U64 posKey;

    S_UNDO history[MAX_POS_MOVES];



} S_BOARD;


// init.c

extern int KnightMovesOnSq[BRD_SQ_NUM][8]; // sq - moves
extern int SlidingMovesOnSq[BRD_SQ_NUM][8][7]; // sq - dir - moves
extern void AllInit();

// bitboards.c

extern void printBitBoard(U64 bb);
extern int CountBits(U64 bb);
extern int PopBit(U64 *bb);

#endif