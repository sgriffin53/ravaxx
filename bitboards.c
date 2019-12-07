#include "position.h"
#include "globals.h"
#include "attacks.h"
#include "bitboards.h"

const U64 BBfileA = 0b0000001\
0000001\
0000001\
0000001\
0000001\
0000001\
0000001;

const U64 BBfileB = 0b0000010\
0000010\
0000010\
0000010\
0000010\
0000010\
0000010;

const U64 BBfileC = 0b0000100\
0000100\
0000100\
0000100\
0000100\
0000100\
0000100;

const U64 BBfileD = 0b0001000\
0001000\
0001000\
0001000\
0001000\
0001000\
0001000;

const U64 BBfileE = 0b0010000\
0010000\
0010000\
0010000\
0010000\
0010000\
0010000;

const U64 BBfileF = 0b0100000\
0100000\
0100000\
0100000\
0100000\
0100000\
0100000;

const U64 BBfileG = 0b1000000\
1000000\
1000000\
1000000\
1000000\
1000000\
1000000;

U64 northOne(U64 BB) {
	return BB << 7 & ONBOARD;
}
U64 southOne(U64 BB) {
	return BB >> 7 & ONBOARD;
}
U64 westOne(U64 BB) {
	return (BB >> 1) & ~BBfileG & ONBOARD;
	//else return 0ULL;
}
U64 eastOne(U64 BB) {
	return (BB << 1) & ~BBfileA & ONBOARD;
}
/*
U64 soEaOne(U64 BB) {
	return (BB >> 7) & ~BBfileA & ONBOARD;
}
U64 soWeOne(U64 BB) {
	return (BB >> 9) & ~BBfileH & ONBOARD;
}
U64 noEaOne(U64 BB) {
	return (BB << 9) & ~BBfileA & ONBOARD;
}
U64 noWeOne(U64 BB) {
	return (BB << 7) & ~BBfileH & ONBOARD;
}
*/