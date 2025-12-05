

#include <stdio.h>
#include "defs.h"

void SetPiece(int p, int sq, S_BOARD *pos)
{
    SetBit(&(pos->bitBoards[p]), sq);
    pos->pieces[sq] = p;
    ClearBit(&(pos->emptyBB), sq);
    if (p >= wK && p <= wQ)
    {
        SetBit(&(pos->whiteBB), sq);
    }
    else if (p >= bK && p <= bQ)
    {
        SetBit(&(pos->blackBB), sq);
    }
}

void RemovePiece(int p, int sq, S_BOARD *pos)
{
    ClearBit(&(pos->bitBoards[p]), sq);
    pos->pieces[sq] = EMPTY;
    SetBit(&(pos->emptyBB), sq);
    if (p >= wK && p <= wQ)
    {
        ClearBit(&(pos->whiteBB), sq);
    }
    else if (p >= bK && p <= bQ)
    {
        ClearBit(&(pos->blackBB), sq);
    }
}

void ResetBoard(S_BOARD *pos)
{
    int i = 0;
    for (i = 0; i < BRD_SQ_NUM; ++i)
    {
        pos->pieces[i] = EMPTY;
    }
    for (i = 0; i < 13; ++i)
    {
        pos->bitBoards[i] = 0ULL;
    }
    pos->blackBB = 0ULL;
    pos->whiteBB = 0ULL;
    pos->emptyBB = ~0ULL;
    pos->toMove = BOTH;
    pos->epSq = NO_SQ;
    pos->fiftyMove = 0;
    pos->ply = 0;
    pos->hisPly = 0;
    pos->castlePerm = 0;
    pos->posKey = 0ULL;
}

int IsCheck(S_BOARD *board, int sq)
{
    // check if sq is controlled by enemy
    int offset = (board->toMove == WHITE) ? 0 : 6;
    U64 friendBB = (board->toMove == WHITE) ? board->whiteBB : board->blackBB;
    U64 enemBB = (board->toMove == WHITE) ? board->blackBB : board->whiteBB;
    // check knight moves away
    for (int i = 0; i < 8; i++)
    {
        int target = KnightMovesOnSq[sq][i];
        if (target == NO_SQ)
        {
            break;
        }
        if (SetMask[target] & board->bitBoards[wN + offset])
        {
            return 1;
        }
    }
    // check sliding moves
    for (int d = 0; d < 8; ++d)
    {
        for (int i = 0; i < 7; i++)
        {
            int target = SlidingMovesOnSq[sq][d][i];
            if (target == NO_SQ)
            {
                break;
            }
            if (SetMask[target] & friendBB)
            {
                break;
            }
            if (d == 0 || d == 2 || d == 5 || d == 7)
            {
                // check bishop or queen
                if (SetMask[target] & board->bitBoards[wB + offset] || SetMask[target] & board->bitBoards[wQ + offset])
                {
                    return 1;
                }
            }
            else
            {
                if (SetMask[target] & board->bitBoards[wR + offset] || SetMask[target] & board->bitBoards[wQ + offset])
                {
                    return 1;
                }
            }
        }
    }
    // no checks found
    return 0;
}

int LoadFen(char *FEN, S_BOARD *pos)
{
    int rank = RANK_1;
    int file = FILE_A;
    int piece = 0;
    int sq64;
    int count;
    int i;
    ResetBoard(pos);

    while ((rank <= RANK_8) && *FEN)
    {
        count = 1;
        switch (*FEN)
        {
        case 'K':
            piece = wK;
            break;
        case 'P':
            piece = wP;
            break;
        case 'N':
            piece = wN;
            break;
        case 'B':
            piece = wB;
            break;
        case 'R':
            piece = wR;
            break;
        case 'Q':
            piece = wQ;
            break;
        case 'k':
            piece = bK;
            break;
        case 'p':
            piece = bP;
            break;
        case 'n':
            piece = bN;
            break;
        case 'b':
            piece = bB;
            break;
        case 'r':
            piece = bR;
            break;
        case 'q':
            piece = bQ;
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            piece = EMPTY;
            count = *FEN - '0';
            break;

        case '/':
        case ' ':
            rank++;
            file = FILE_A;
            FEN++;
            continue;

        default:
            printf("FEN error\n");
            return -1;
        }

        for (i = 0; i < count; i++)
        {
            sq64 = rank * 8 + file;
            if (piece != EMPTY)
            {
                SetPiece(piece, sq64, pos);
            }
            file++;
        }
        FEN++;
    }
    // set side to move
    pos->toMove = (*FEN == 'w') ? WHITE : BLACK;
    FEN += 2;
    // set casteling perm
    for (i = 0; i < 4; i++)
    {
        if (*FEN == ' ')
        {
            break;
        }
        switch (*FEN)
        {
        case 'K':
            pos->castlePerm |= WKCA;
            break;
        case 'Q':
            pos->castlePerm |= WQCA;
            break;
        case 'k':
            pos->castlePerm |= BKCA;
            break;
        case 'q':
            pos->castlePerm |= BQCA;
            break;
        default:
            break;
        }
        FEN++;
    }
    FEN++;

    // set ep square
    if (*FEN != '-')
    {
        file = 8 - (FEN[0] - 'a');
        rank = FEN[1] - '1';
        pos->epSq = rank + 8 * file;
    }

    // gen hash
    pos->posKey = GeneratePosKey(pos);

    return 0;
}

void PrintBoard(S_BOARD *pos)
{
    for (int i = 0; i < BRD_SQ_NUM; ++i)
    {
        if (i % 8 == 0)
            printf("%d   ", 8 - i / 8);
        int piece = pos->pieces[i];
        char piece_char;
        switch (piece)
        {
        case wK:
            piece_char = 'K';
            break;
        case wP:
            piece_char = 'P';
            break;
        case wN:
            piece_char = 'N';
            break;
        case wB:
            piece_char = 'B';
            break;
        case wR:
            piece_char = 'R';
            break;
        case wQ:
            piece_char = 'Q';
            break;
        case bK:
            piece_char = 'k';
            break;
        case bP:
            piece_char = 'p';
            break;
        case bN:
            piece_char = 'n';
            break;
        case bB:
            piece_char = 'b';
            break;
        case bR:
            piece_char = 'r';
            break;
        case bQ:
            piece_char = 'q';
            break;
        default:
            piece_char = '.';
            break;
        }
        printf("  %c", piece_char);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n    ");
    for (int file = 0; file <= FILE_H; ++file)
    {
        printf("  %c", 'a' + file);
    }
    printf("\n\n");
    printf("Side: %c\n",
           (pos->toMove == WHITE) ? 'w' : 'b');
    printf("Ep sq: %d\n", pos->epSq);
    printf("CP: %c%c%c%c\n",
           pos->castlePerm & WKCA ? 'K' : '-',
           pos->castlePerm & WQCA ? 'Q' : '-',
           pos->castlePerm & BKCA ? 'k' : '-',
           pos->castlePerm & BQCA ? 'q' : '-');
    printf("PosKey: %llx\n", pos->posKey);
}

void BoardPrintBitBorads(S_BOARD *pos)
{
    for (int i = 1; i < 13; ++i)
    {
        printf("BB %d:\n", i);
        printBitBoard(pos->bitBoards[i]);
    }
    printf("black BB:\n");
    printBitBoard(pos->blackBB);
    printf("white BB:\n");
    printBitBoard(pos->whiteBB);
    printf("empty BB:\n");
    printBitBoard(pos->emptyBB);
}

void MakeMove(U32 m, S_BOARD *pos)
{
    unsigned int start = m & 0b111111;
    unsigned int target = (m & 0b111111000000) >> 6;
    unsigned int flag = m & ~(0b111111111111) >> 12;
    int s_piece = pos->pieces[start];
    int t_piece = pos->pieces[target];
    // save current board details
    S_UNDO um = {m, pos->castlePerm, pos->epSq, pos->fiftyMove, pos->posKey, t_piece};
    pos->ply += 1;
    pos->history[pos->hisPly] = um;
    pos->hisPly += 1;
    // make move
    switch (flag)
    {
    default:
        RemovePiece(s_piece, start, pos);
        RemovePiece(t_piece, target, pos);
        SetPiece(s_piece, target, pos);
        break;
    }
    // update castle perms and ep

    // pass turn
    pos->toMove = (pos->toMove == WHITE) ? BLACK : WHITE;
}

void UnDoMove(S_BOARD *pos)
{
    pos->hisPly -= 1;
    if (pos->hisPly < 0)
    {
        return;
    }
    S_UNDO um = pos->history[pos->hisPly];
    U32 m = um.move;
    unsigned int start = m & 0b111111;
    unsigned int target = (m & 0b111111000000) >> 6;
    unsigned int flag = m & ~(0b111111111111) >> 12;
    int s_piece = pos->pieces[target];
    int t_piece = um.captured_piece;

    switch (flag)
    {
    default:
        RemovePiece(s_piece, target, pos);
        SetPiece(s_piece, start, pos);
        if (t_piece != EMPTY)
            SetPiece(t_piece, target, pos);
        break;
    }
    pos->castlePerm = um.castlePerm;
    pos->epSq = um.epSq;
    pos->fiftyMove = um.fiftyMove;
    pos->posKey = um.posKey;

    pos->ply -= 1;
    pos->toMove = (pos->toMove == WHITE) ? BLACK : WHITE;
}
