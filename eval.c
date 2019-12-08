#include "position.h"
#include "globals.h"
#include "attacks.h"

const int PST[49] = {30, 20, 10, 10, 10, 20, 30, 20, 10, 10, 5,  10, 10,
                     20, 10, 10, 5,  0,  5,  10, 10, 10, 5,  0,  0,  0,
                     5,  10, 10, 10, 5,  0,  5,  10, 10, 20, 10, 10, 5,
                     10, 10, 20, 30, 20, 10, 10, 10, 20, 30};
					 
int taperedEval(struct position *pos) {
	int eval = 100 * (__builtin_popcountll(pos->Xpieces) - __builtin_popcountll(pos->Opieces));
	U64 BBX = pos->Xpieces;
	while (BBX) {
		int square = __builtin_ctzll(BBX);
		BBX &= BBX - 1;
		eval += PST[square] / 5;
	}
	U64 BBO = pos->Opieces;
	while (BBO) {
		int square = __builtin_ctzll(BBO);
		BBO &= BBO - 1;
		eval -= PST[square] / 5;
	}
	
	// mobility
	
	int Xmob = 0;
	int Omob = 0;
	BBX = pos->Xpieces;
	while (BBX) {
		int square = __builtin_ctzll(BBX);
		BBX &= BBX - 1;
		U64 BBsingles = BBsurrounding(1ULL << square) & ~pos->Opieces & ~pos->Xpieces & ONBOARD;
		U64 BBdoubles = BBdoublesLookup[square] & ~pos->Opieces & ~pos->Xpieces;
		Xmob += __builtin_popcountll(BBsingles | BBdoubles);
	}
	BBX = pos->Opieces;
	while (BBO) {
		int square = __builtin_ctzll(BBO);
		BBO &= BBO - 1;
		U64 BBsingles = BBsurrounding(1ULL << square) & ~pos->Opieces & ~pos->Xpieces & ONBOARD;
		U64 BBdoubles = BBdoublesLookup[square] & ~pos->Opieces & ~pos->Xpieces;
		Omob += __builtin_popcountll(BBsingles | BBdoubles);
	}
	eval += Xmob / 40;
	eval -= Omob / 40;
	if (pos->tomove == O) return -eval;
	return eval;
}