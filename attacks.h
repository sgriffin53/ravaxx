#ifndef ATTACKS_H
#define ATTACKS_H

#include "position.h"

U64 BBsurrounding(U64 BBpiece);
void capturePieces(struct position *pos, int square, int side);

void genLookups();
#endif