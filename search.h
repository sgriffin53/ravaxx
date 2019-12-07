#ifndef SEARCH_H
#define SEARCH_H

struct move search(struct position pos, int searchdepth, int movetime);
int alphaBeta(struct position *pos, int alpha, int beta, int depth, int ply, struct move *pv, clock_t endtime);

#endif