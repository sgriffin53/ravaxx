#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "position.h"
#include "move.h"
#include "makemove.h"
#include "bitboards.h"
#include "globals.h"
#include "movegen.h"
#include "perft.h"
#include "makemove.h"
#include "attacks.h"
#include "search.h"

int main() {
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	char instr[8192];
	char splitstr[1000][200];
	char * token;
	int keeprunning = 1;
	
	struct position pos;
	parsefen(&pos, "startpos");
	
ONBOARD = (U64)0b1111111\
1111111\
1111111\
1111111\
1111111\
1111111\
1111111; // set first 49 bits of ONBOARD for reference to which squares are on the board
	
	genLookups();
	
	U64 BBboard;
	//BBboard = BBsurrounding(1ULL << 49);
	//BBboard = BBsurrounding(1ULL << 42);
	//printf("%d",BBboard);
	//dspBB(BBboard);
	//dspBB(BBfileG);
	while (keeprunning) {
		// read input from stdin
		fgets(instr, 8192, stdin);
		// removes newline character from input
		instr[strcspn(instr, "\n")] = 0;
		//split instr into tokens into splitstr by space
		token = strtok(instr," ");

		int splitstrend = 0;
		while (token != NULL) {
			strcpy(splitstr[splitstrend],token);
			splitstrend++;
			token = strtok(NULL, " ");
		}
		if (strcmp(splitstr[0],"moves") == 0) {
			for (int i = 1;i < splitstrend;i++) {
				// make move
				//makeMovestr(splitstr[i],&pos);
				makeMovestr(&pos, splitstr[i]);
			}
		}
		if (strcmp(splitstr[0],"uainewgame") == 0) {
		}
		if (strcmp(splitstr[0],"board") == 0) {
			dspBoard(&pos);
		}
		if (strcmp(splitstr[0],"perft") == 0) {
			int depth;
			U64 pnodes;
			U64 nps;
			depth = atoi(splitstr[1]);
			for (int i = 1;i <= depth;i++) {
				clock_t begin = clock();
				pnodes = perft(&pos,i);
				clock_t end = clock();
				double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
				nps = pnodes / time_spent;
				printf("info depth %d nodes %" PRIu64 " time %d nps %" PRIu64 "\n",i,pnodes,(int)(1000 * time_spent),nps);
			}

			printf("nodes %" PRIu64 "\n", pnodes);
		}
		else if (strcmp(splitstr[0],"sperft") == 0) {
		}
		if (strcmp(splitstr[0],"move") == 0) {
			makeMovestr(&pos, splitstr[1]);
			//struct move mymove;
			//mymove.type = SINGLE;
			//mymove.from = 6;
			//mymove.to = 5;
			//makeMove(&pos, &mymove);
		}
		if (strcmp(splitstr[0],"unmove") == 0) {
			unmakeMove(&pos);
		}
		if (strcmp(splitstr[0],"legalmoves") == 0) {
			struct move moves[2048];
			int num_moves = genLegalMoves(&pos, moves);
			for (int i = 0;i < num_moves;i++) {
				printf("%s\n",movetostr(moves[i]));
			}
		}
		if (strcmp(splitstr[0],"isready") == 0) {
			printf("readyok\n");
		}
		else if (strcmp(splitstr[0],"uai") == 0) {
			printf("id name Ravaxx 0.10\nid author Steve Griffin\n");
			printf("uaiok\n");
		}
		
		else if (strcmp(splitstr[0],"go") == 0) {
			int searchdepth = 100;
			//movetime = 2147483646;
			int movetime = INT_MAX / 100;

			if (strcmp(splitstr[1],"depth") == 0) {
				searchdepth = atoi(splitstr[2]);
			}
			
			wtime = -1;
			btime = -1;
			for (int i = 1;i < splitstrend;i++) {
				if (strcmp(splitstr[i],"wtime") == 0) {
					wtime = atoi(splitstr[i+1]);
					if (origwtime == -1) origwtime = wtime;
				}
				if (strcmp(splitstr[i],"btime") == 0) {
					btime = atoi(splitstr[i+1]);
					if (origbtime == -1) origbtime = btime;
				}
			}
			if (pos.tomove == X) {
				if (wtime != -1) movetime = wtime / 25;
			}
			else {
				if (btime != -1) movetime = btime / 25;
			}
			 
			if (strcmp(splitstr[1],"movetime") == 0) {
				movetime = atoi(splitstr[2]);
			}

			nodesSearched = 0;

			search(pos,searchdepth,movetime);
		}
		else if (strcmp(splitstr[0],"quit") == 0) {
			keeprunning = 0;
		}
		else if ( (strcmp(splitstr[0],"position") == 0) && (strcmp(splitstr[1],"startpos") == 0) ) {
			parsefen(&pos, "startpos"); // set start position
			if (strcmp(splitstr[2],"moves") == 0) {
				// make all moves given by position command
				for (int i = 3;i < splitstrend;i++) {
					// make move
					makeMovestr(&pos,splitstr[i]);
				}
			}
		}
		else if ( (strcmp(splitstr[0],"position") == 0) && (strcmp(splitstr[1],"fen") == 0) ) {
			char fen[1024] = "";
			int readingfen = 1;
			for (int i = 2;i < splitstrend;i++) {
				if (!readingfen) {
					makeMovestr(&pos,splitstr[i]);
				}
				if (strcmp(splitstr[i],"moves") == 0) {
					parsefen(&pos, fen);
					readingfen = 0;
				}
				if (readingfen) {
					strcat(fen,splitstr[i]);
					if (i != (splitstrend - 1)) strcat(fen," ");
				}
			}
			if (readingfen) {
				parsefen(&pos, fen);
			}
		}
	}
	
	return 0;
}
