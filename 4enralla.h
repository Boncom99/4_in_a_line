#ifndef ENRALLA_H
#define ENRALLA_H
#include "minimax.h"
#include "node.h"
void printLine();
void printNumbers();
void printBoard(char b[N][N]);
void askMove(unsigned int *move);
int estaFora(int row, int col);
int checkHorizontal(Node *p, int player, int row, int col, int count);
int checkVertical(Node *p, int player, int row, int col, int count);
int win(Node *p);
int isFull(Node *p);
char finish(Node *p);
unsigned int fall(Node *p, unsigned int col);
void placeChip(Node *p, unsigned int row, unsigned int col, char player);
char *checkColumns(Node *p);
void move(Node *p, char player);

#endif