#ifndef RANDPIECETYPE_INCLUDED
#define RANDPIECETYPE_INCLUDED

#include <cstdlib>

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

static PieceType randPieceType()
{
    return(static_cast<PieceType>(std::rand() % NUM_PIECE_TYPES));
}

#endif // RANDPIECETYPE_INCLUDED
