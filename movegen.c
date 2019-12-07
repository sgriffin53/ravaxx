#include "position.h"
#include "move.h"
#include "makemove.h"
#include "attacks.h"
#include "globals.h"
#include "movegen.h"
#include <string.h>
#include <stdio.h>

int genSquareMoves(struct position *pos, struct move *moves, int square) {
	int num_moves = 0;
	U64 BBaround = BBdoublesLookup[square] & ~pos->Opieces & ~pos->Xpieces;
	while (BBaround) {
		int tosquare = __builtin_ctzll(BBaround);
		BBaround &= BBaround - 1;
		moves[num_moves].from = square;
		moves[num_moves].to = tosquare;
		moves[num_moves].type = DOUBLE;
		num_moves++;
	}
	return num_moves;
}
int genLegalMoves(struct position *pos, struct move *moves) {
	U64 BBpieces;
	int num_moves = 0;
	if (pos->tomove == X) BBpieces = pos->Xpieces;
	else BBpieces = pos->Opieces;
	
	// generate singles
	U64 BBsingles = BBsurrounding(BBpieces) & ~pos->Opieces & ~pos->Xpieces & ONBOARD;
	while (BBsingles) {
		int square = __builtin_ctzll(BBsingles);
		BBsingles &= BBsingles - 1;
		moves[num_moves].from = -1;
		moves[num_moves].to = square;
		moves[num_moves].type = SINGLE;
		num_moves++;
	}
	while (BBpieces) {
		int square = __builtin_ctzll(BBpieces);
		BBpieces &= BBpieces - 1;
		num_moves += genSquareMoves(pos, &moves[num_moves], square);
	}
	if (num_moves == 0) {
		// no moves available - create a passing move
		moves[num_moves].from = -1;
		moves[num_moves].to = -1;
		moves[num_moves].type = PASS;
		num_moves++;
	}
	return num_moves;
}