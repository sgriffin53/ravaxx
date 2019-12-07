#include "position.h"
#include "bitboards.h"
#include "globals.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int fileranktosquareidx(int file,int rank) {
	return (rank) * 7 + file;
}

void parsefen(struct position *pos, const char *ofen) {
	
	if (strncmp(ofen, "startpos", 8) == 0) {
		parsefen(pos, "x5o/7/7/7/7/7/o5x x 0 1");
		return;
	}
	char fen[strlen(ofen)];
	strcpy(fen, ofen);

	char splitstr[100][8192];
	char * token;
	
	
	// set blank position
	memset(pos, 0, sizeof(struct position));
	
	int n = 0;
	token = strtok(fen," ");
	while (token != NULL) {
		strcpy(splitstr[n],token);
		n++;
		token = strtok(NULL, " ");
	}
	pos->tomove = X;
	int j = 0;
	for (int i = 0;i < (int)strlen(splitstr[0]);i++) {
		char letter = splitstr[0][i];
		int realrank = 6 - (j/7);
		int realfile = j % 7;
		int a = fileranktosquareidx(realfile,realrank);
		//printf("%d\n", a);
		switch (letter) {
			case 'x': {
				pos->Xpieces |= 1ULL << a;
				break;
			}
			case 'o': {
				pos->Opieces |= 1ULL << a;
				break;
			}
			case '/': j--; break;
			case '1' : break;
			case '2' : j++; break;
			case '3' : j+=2; break;
			case '4' : j+=3; break;
			case '5' : j+=4; break;
			case '6' : j+=5; break;
			case '7' : j+=6; break;
			case '8' : j+=7; break;
		}
		j++;
	}
	if (splitstr[1][0] == 'x') pos->tomove = X;
	else if (splitstr[1][0] == 'o') pos->tomove = O;
	pos->halfmoves = atoi(splitstr[2]);
	pos->fullmoves = atoi(splitstr[3]);
	posstackend = 1;
	posstack[0] = *pos;
}
int getPiece(struct position *pos, int square) {
	if (pos->Xpieces & 1ULL << square) return X;
	else if (pos->Opieces & 1ULL << square) return O;
	return EMPTY;
}
void setPiece(struct position *pos, int square, int piece) {
	if (piece == X) {
		pos->Xpieces |= 1ULL << square;
	}
	else if (piece == O) {
		pos->Opieces |= 1ULL << square;
	}
	else if (piece == EMPTY) {
		pos->Opieces &= ~(1ULL << square);
		pos->Xpieces &= ~(1ULL << square);
	}
}
int getrank(int square) {
	return square / 7;
}

int getfile(int square) {
	return square % 7;
}
void dspBoard(struct position *pos) {
	
	printf("\n");
	printf("  +---+---+---+---+---+---+---+\n");
	printf("7 |");
	
	int rank = 0;
	int file = 0;
	int sq = 0;
	for (rank = 6;rank >= 0;rank--) {
		for (file = 0;file <= 6;file++) {
			sq = fileranktosquareidx(file,rank);
			int piece = getPiece(pos,sq);
			char printpiece;
			if (piece == EMPTY) printpiece = ' ';
			else if (piece == X) printpiece = 'x';
			else if (piece == O) printpiece = 'o';
			printf(" %c |",printpiece);
		}
		printf("\n");
		printf("  +---+---+---+---+---+---+---+\n");
		if ((sq/7) != 0) {
			printf("%d",(sq/7));
			printf(" |");
		}
	}
	printf("    A   B   C   D   E   F   G  \n");
	printf("To move: ");
	if (pos->tomove == X) printf("X");
	else printf("O");
	printf("\n");
}
void dspBB(U64 BB) {
	
	printf("\n");
	printf("  +---+---+---+---+---+---+---+\n");
	printf("7 |");
	
	int rank = 0;
	int file = 0;
	int sq = 0;
	for (rank = 6;rank >= 0;rank--) {
		for (file = 0;file <= 6;file++) {
			sq = fileranktosquareidx(file,rank);
			//printf("%d\n", sq);
			if ((1ULL << sq) & BB) {
				printf(" 1 |");
			}
			else {
				printf(" 0 |");
			}
		}
		printf("\n");
		printf("  +---+---+---+---+---+---+---+\n");
		if ((sq/7) != 0) {
			printf("%d",(sq/7));
			printf(" |");
		}
	}
	printf("    A   B   C   D   E   F   G   \n");
}