#include "position.h"
#include "bitboards.h"
#include "globals.h"
#include "makemove.h"
#include "movegen.h"
#include "move.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

U64 perft(struct position *pos, int depth) {

	if (depth == 0) return 1;

	U64 nodes = 0;
	struct move moves[2048];
	const int n_moves = genLegalMoves(pos,moves);

	for (int i = 0; i < n_moves;i++) {
		makeMove(pos, &moves[i]);

		nodes += perft(pos, depth - 1);

		unmakeMove(pos);
	}

	return nodes;
}