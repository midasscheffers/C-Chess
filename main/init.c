

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define RAND_64 ((U64)rand() |       \
                 (U64)rand() << 15 | \
                 (U64)rand() << 30 | \
                 (U64)rand() << 45 | \
                 ((U64)rand() & 0xf) << 60)

// Init hashkeys
U64 PieceKeys[13][64];
U64 sideKey;
U64 castleKey[16];

void InitHashKeys()
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 13; i++)
    {
        for (j = 0; j < 64; j++)
        {
            PieceKeys[i][j] = RAND_64;
        }
    }
    sideKey = RAND_64;
    for (i = 0; i < 16; i++)
    {
        castleKey[i] = RAND_64;
    }
}

// check if a x,y pos is on the board
int onBoard(int x, int y)
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
    {
        return FALSE;
    }
    return TRUE;
}

// precalcualte knight moves
int KnightMovesOnSq[BRD_SQ_NUM][8];

void InitKnightMoves()
{

    for (int i = 0; i < BRD_SQ_NUM; i++)
    {
        int x = i % 8;
        int y = i / 8;
        int index = -1;
        for (int j = -2; j < 3; j++)
        {
            for (int k = -2; k < 3; k++)
            {
                if (abs(k) != abs(j) && k != 0 && j != 0)
                {
                    if (onBoard(x + k, y + j))
                    {
                        index += 1;
                        int target = (x + k) + 8 * (y + j);
                        KnightMovesOnSq[i][index] = target;
                    }
                }
            }
        }
        for (index++; index < 8; index++)
        {
            KnightMovesOnSq[i][index] = NO_SQ;
        }
    }
}

// precalcualte sliding moves
int SlidingMovesOnSq[BRD_SQ_NUM][8][7];

void InitSlidingMoves()
{
    for (int i = 0; i < BRD_SQ_NUM; i++)
    {
        int x = i % 8;
        int y = i / 8;
        int dir[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
        // for dir
        for (int d = 0; d < 8; d++)
        {
            int index = 0;
            int curr_dir[2] = {dir[d][0], dir[d][1]};
            for (index; index < 7; index++)
            {
                int dx = (index + 1) * curr_dir[0];
                int dy = (index + 1) * curr_dir[1];
                if (onBoard(x + dx, y + dy))
                {
                    int target = (x + dx) + 8 * (y + dy);
                    SlidingMovesOnSq[i][d][index] = target;
                }
                else
                {
                    break;
                }
            }
            for (index; index < 7; index++)
            {
                SlidingMovesOnSq[i][d][index] = NO_SQ;
            }
        }
    }
}

// masks for fast setting and clearing bits
U64 SetMask[64];
U64 ClearMask[64];

void InitSetClearMasks()
{
    int index = 0;
    for (index; index < BRD_SQ_NUM; index++)
    {
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }
    index = 0;
    for (index; index < BRD_SQ_NUM; index++)
    {
        SetMask[index] = 1ULL << index;
        ClearMask[index] = ~SetMask[index];
    }
}

// set possible moves to the null array;
U32 possible_moves[MAX_POS_MOVES_ONE_POS];
void InitGenMoves()
{
    for (int i = 0; i < MAX_POS_MOVES_ONE_POS; i++)
    {
        possible_moves[i] = NULL_MOVE;
    }
}

void AllInit()
{
    InitHashKeys();
    InitKnightMoves();
    InitSlidingMoves();
    InitSetClearMasks();
    InitGenMoves();
}