#ifndef MAKEMOVE_H
#define MAKEMOVE_H

#include "position.h"
#include "move.h"

void makeMove(struct position *pos, struct move *move);
int strsquaretoidx(char square[]);
void makeMovestr(struct position *pos, const char move[]);
void unmakeMove(struct position *pos);

#endif