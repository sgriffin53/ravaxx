#include "position.h"
#include "globals.h"
#include "attacks.h"

int taperedEval(struct position *pos) {
	int eval = 100 * (__builtin_popcountll(pos->Xpieces) - __builtin_popcountll(pos->Opieces));
	if (pos->tomove == O) return -eval;
	return eval;
}