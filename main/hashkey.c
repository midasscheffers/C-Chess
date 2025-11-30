

#include "defs.h"



U64 GeneratePosKey(const S_BOARD *pos){
    int sq = 0;
    U64 finalkey = 0;
    int piece = EMPTY;

    //add pieces keys
    for (sq = 0; sq<BRD_SQ_NUM; ++sq){
        piece = pos->pieces[sq];
        if (piece!=EMPTY){
            finalkey ^= PieceKeys[piece][sq];
        }
        if (pos->toMove == WHITE){
            finalkey ^= sideKey;
        }
        if (pos->epSq != NO_SQ){
            finalkey ^= PieceKeys[EMPTY][pos->epSq];
        }
        finalkey ^= castleKey[pos->castlePerm];

        return finalkey;
    }
}