#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include <string.h>
#include <stdio.h>

#define SINGLE 0
#define DOUBLE 1
#define PASS 2

struct move {
	int from;
	int to;
	int type;
};
static inline char* movetostr(struct move move) {
	if (move.type == PASS) return "0000";
	char returnstring[6];
	char startsquarefile = (char)(getfile(move.from) + 97);
	char startsquarerank = (char)(getrank(move.from) + 49);
	char endsquarefile = (char)(getfile(move.to) + 97);
	char endsquarerank = (char)(getrank(move.to) + 49);
	if (move.type == DOUBLE) {
		returnstring[0] = startsquarefile;
		returnstring[1] = startsquarerank;
		returnstring[2] = endsquarefile;
		returnstring[3] = endsquarerank;
		returnstring[4] = 0;
	}
	else if (move.type == SINGLE) {
		returnstring[0] = endsquarefile;
		returnstring[1] = endsquarerank;
		returnstring[2] = 0;
	}
	return strdup(returnstring);
}
#endif