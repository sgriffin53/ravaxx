#ifndef MOVEGEN_H
#define MOVEGEN_H

int genSquareMoves(struct position *pos, struct move *moves, int square);
int genLegalMoves(struct position *pos, struct move *moves);

#endif