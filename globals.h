#ifndef GLOBALS_H
#define GLOBALS_H

#include "position.h"

struct position posstack[1024];
int posstackend;
U64 ONBOARD;
U64 BBdoublesLookup[49];
int seldepth;
int nodesSearched;
int origwtime, origbtime, wtime, btime;
#endif