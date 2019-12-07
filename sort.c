#include "position.h"
#include "move.h"
#include "attacks.h"

void sortMoves(struct position *pos, struct move *moves, int num_moves) {
	int scores[num_moves];
	U64 BBopppieces;
	if (pos->tomove == X) BBopppieces = pos->Opieces;
	else BBopppieces = pos->Xpieces;
	for (int i = 0;i < num_moves;i++) {
		//scores[i] = 0;
		int cappieces = __builtin_popcountll(BBsurrounding(moves[i].to) & BBopppieces);
		scores[i] = cappieces;
		if (moves[i].type == SINGLE) scores[i] = 1000 + cappieces;
	}
	
	int i, j;
	for (i = 0;i < num_moves - 1;i++) {
		int min_idx = i;
		for (j = i+1; j < num_moves;j++) {
			if (scores[j] > scores[min_idx]) min_idx = j;
		}
		int scorecopy = scores[i];
		scores[i] = scores[min_idx];
		scores[min_idx] = scorecopy;
		
		struct move movecopy = moves[i];
		moves[i] = moves[min_idx];
		moves[min_idx] = movecopy;
	}
}