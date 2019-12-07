#include "position.h"
#include "move.h"
#include "globals.h"
#include "attacks.h"
#include "eval.h"
#include "movegen.h"
#include "makemove.h"
#include <time.h>
#include <limits.h>
#include "sort.h"

#define MATE_SCORE 9999

int alphaBeta(struct position *pos, int alpha, int beta, int depth, int ply, struct move *pv, clock_t endtime) {
	nodesSearched++;
	if (ply > seldepth) seldepth = ply;
	if (clock() >= endtime) {
		return -MATE_SCORE;
	}
	if (pos->halfmoves >= 100) return 0;
	int Xstones = __builtin_popcountll(pos->Xpieces);
	int Ystones = __builtin_popcountll(pos->Opieces);
	int stones = Xstones + Ystones;
	if (stones == 49) {
		if (Xstones > Ystones) {
			// X has won
			if (pos->tomove == X) return MATE_SCORE;
			else return -MATE_SCORE;
		}
		if (Xstones < Ystones) {
			// O has won
			if (pos->tomove == O) return MATE_SCORE;
			else return -MATE_SCORE;
		}
		else return 0;
	}
	if (depth <= 0) return taperedEval(pos);
	
	int bestscore = INT_MIN;
	struct move bestmove = {.to=-1, .from=-1, .type=-1};
	
	int score = 0;
	
	struct move moves[2048];
	int num_moves = genLegalMoves(pos, moves);
	sortMoves(pos, moves, num_moves);
	
	for (int i = 0;i < num_moves;i++) {
		makeMove(pos, &moves[i]);
		int r = 0;
		int extension = 0;
		
		U64 BBopppieces;
		if (pos->tomove == O) BBopppieces = pos->Opieces;
		else BBopppieces = pos->Xpieces;
		int cappieces = __builtin_popcountll(BBsurrounding(moves[i].to) & BBopppieces);
		
		if (depth >= 3 && i > 25 && cappieces <= 3) r = 1;
		score = -alphaBeta(pos, -beta, -alpha, depth - 1 - r + extension, ply + 1, pv, endtime);
		if (r > 0 && score > alpha) {
			score = -alphaBeta(pos, -beta, -alpha, depth - 1 + extension, ply + 1, pv, endtime);
		}
		unmakeMove(pos);
		if (score > bestscore) {
			bestscore = score;
			bestmove = moves[i];
		}
		if (bestscore > alpha) {
			alpha = bestscore;
		}
		if (alpha >= beta) {
			break;
		}
	}
	*pv = bestmove;
	return bestscore;
}

struct move search(struct position pos, int searchdepth, int movetime) {

	// Reset stats
	nodesSearched = 0;

	//for (int i = 0;i < 1024;i++) {
	//	hashstack[i] = 0;
	//}
	
	// Result
	struct move bestmove;
	
	seldepth = 0;
	
	double time_spent;
	int time_spentms;
	
	// Timing code
	const clock_t begin = clock();
	clock_t endtime = clock() + (movetime / 1000.0 * CLOCKS_PER_SEC);
	clock_t maxendtime = endtime + (movetime * 1 / 1000.0 * CLOCKS_PER_SEC);
	clock_t origendtime = endtime;
	
	//printf("start %d end %d maxend %d\n",begin,endtime,maxendtime);
	// Movegen
	struct move moves[2048];
	const int num_moves = genLegalMoves(&pos, moves);
	
	struct move pv;
	
	int time_spent_prevms;
	int score = 0;
	int lastscore = 0;
	int lastlastscore = 0;
	struct move pvlist[128];
	for(int d = 1; d <= searchdepth; ++d) {
		
		time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
		time_spentms = (int)(time_spent*1000);

		score = alphaBeta(&pos, -MATE_SCORE, MATE_SCORE, d, 0, &pv, endtime);
		
		//Ignore the result if we ran out of time
		if (d > 1 && clock() >= endtime) {
			break;
		}
		
		// Get our TT entry
		//const struct TTentry TTdata = getTTentry(&TT, hash);
		//assert(TTdata.hash == hash);
		 
		time_spent_prevms = time_spentms;
		
		// Update results
		//bestmove = TTdata.bestmove;
		bestmove = pv;
		time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
		time_spentms = (int)(time_spent*1000);
		int nps = nodesSearched / time_spent;
		// Info string
		printf("info");
		printf(" depth %i", d);
		printf(" seldepth %i", seldepth);
		printf(" nodes %d", nodesSearched);
		printf(" time %i", (int)(time_spent*1000));
		if (time_spent >= 0.001) printf(" nps %i", nps);
		printf(" score cp %i", score);
		//printf(" pv %s", movetostr(bestmove));
		printf(" pv");
		printf(" %s",movetostr(bestmove));
		printf("\n");
		if (score == MATE_SCORE || score == -MATE_SCORE) break;
	}
	time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
	time_spentms = (int)(time_spent*1000);
	
	printf("bestmove %s\n", movetostr(bestmove));

	return bestmove;
}