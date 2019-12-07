#ifndef POSITION_H
#define POSITION_H

#define X 0
#define O 1
#define EMPTY 2

typedef unsigned long long U64;

struct position {
	U64 Xpieces;
	U64 Opieces;
	U64 gaps;
	int tomove;
	int halfmoves;
	int fullmoves;
};

int fileranktosquareidx(int file,int rank);
void parsefen(struct position *pos, const char *ofen);
int getPiece(struct position *pos, int square);
void dspBoard(struct position *pos);
void setPiece(struct position *pos, int square, int piece);
void dspBB(U64 BB);

int getrank(int square);
int getfile(int square);

#endif