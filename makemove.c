#include "position.h"
#include "move.h"
#include "makemove.h"
#include "globals.h"
#include "attacks.h"
#include <string.h>
#include <stdio.h>

void makeMove(struct position *pos, struct move *move) {
	if (move->type != PASS) {
		if (pos->tomove == X) pos->fullmoves++;
		
		if (move->type == DOUBLE) setPiece(pos, move->from, EMPTY); // remove original piece on double move
		setPiece(pos, move->to, pos->tomove); // set new piece on to square
		
		capturePieces(pos, move->to, pos->tomove); // capture enemy pieces
		
	}
	pos->halfmoves++;
	pos->tomove = !pos->tomove;
	posstack[posstackend] = *pos;
	posstackend++;
}
void unmakeMove(struct position *pos) {
	posstackend--;
	if (posstackend <= 0) {
		posstackend = 1;
		*pos = posstack[0];
	}
	else {
	*pos = posstack[posstackend - 1];
	}
}

void makeMovestr(struct position *pos, const char move[]) {
	char startsquare[3];
	char endsquare[3];
	int startsquareidx;
	int endsquareidx;
	int movetype;
	if (strlen(move) == 4) {
		startsquare[0] = move[0];
		startsquare[1] = move[1];
		startsquare[2] = 0;
		endsquare[0] = move[2];
		endsquare[1] = move[3];
		endsquare[2] = 0;
		movetype = DOUBLE;
		startsquareidx = strsquaretoidx(startsquare);
		endsquareidx = strsquaretoidx(endsquare);
	}
	else {
		endsquare[0] = move[0];
		endsquare[1] = move[1];
		movetype = SINGLE;
		startsquareidx = -1;
		endsquareidx = strsquaretoidx(endsquare);
	}
	struct move moveobj = {.from=startsquareidx,.to=endsquareidx,.type=movetype};
	if (strcmp(move,"0000") == 0) {
		moveobj.from = -1;
		moveobj.to = -1;
		moveobj.type = PASS;
	}
	makeMove(pos, &moveobj);
}
int strsquaretoidx(char square[]) {
	int file = (int)square[0] - 97;
	int rank = (int)square[1] - 49;
	return fileranktosquareidx(file,rank);
}