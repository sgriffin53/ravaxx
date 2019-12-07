#include "position.h"
#include "bitboards.h"
#include "attacks.h"
#include "globals.h"

U64 BBsurrounding(U64 BBpiece) {
	//assert(__builtin_popcountll(BBpiece) == 1);
	// get king attack squares
	U64 BBattacks = eastOne(BBpiece) | westOne(BBpiece); // east and west one
	BBpiece |= BBattacks; // set piece BB to attacks
	BBattacks |= northOne(BBpiece) | southOne(BBpiece); // north, south, nw, ne, sw, se one
	return BBattacks;
}
void capturePieces(struct position *pos, int square, int side) {
	U64 BBopppieces;
	if (side == X) BBopppieces = pos->Opieces;
	else BBopppieces = pos->Xpieces;
	U64 BBcapsquares = BBsurrounding(1ULL << square);
	U64 BBcapped = BBcapsquares & BBopppieces;
	if (side == X) {
		pos->Xpieces |= BBcapped;
		pos->Opieces &= ~BBcapped;
	}
	else {
		pos->Opieces |= BBcapped;
		pos->Xpieces &= ~BBcapped;
	}
}

void genLookups() {
	//dspBB((1 << 1) & ~BBfileA & ONBOARD);
	//dspBB(BBsurrounding(1 << 1));
	
	for (int i = 0;i < 49;i++) {
		U64 BBaround = BBsurrounding(1ULL << i) & ONBOARD;
		//dspBB(BBsurrounding(1));
		U64 BBorigaround = BBaround;
		BBaround = BBsurrounding(BBsurrounding(1ULL << i)) & ONBOARD & ~BBorigaround;
		BBdoublesLookup[i] = BBaround;
		//dspBB(BBaround);
	}
}