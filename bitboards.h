#ifndef BITBOARDS_H
#define BITBOARDS_H

const U64 BBfileA;
const U64 BBfileB;
const U64 BBfileC;
const U64 BBfileD;
const U64 BBfileE;
const U64 BBfileF;
const U64 BBfileG;
const U64 BBfileH;

U64 northOne(U64 BB);
U64 southOne(U64 BB);
U64 westOne(U64 BB);
U64 eastOne(U64 BB);

U64 soEaOne(U64 BB);
U64 soWeOne(U64 BB);
U64 noEaOne(U64 BB);
U64 noWeOne(U64 BB);


#endif