#ifndef ENRALLA_H
#define ENRALLA_H
#include "minimax.h"
#include "node.h"
int askMove();
int estaFora(int row, int col);
int checkHorizontal(Node *p, int player, int row, int col, int count);
int checkVertical(Node *p, int player, int row, int col, int count);
int win(Node *p);
int isFull(Node *p);
char finish(Node *p);
unsigned int fall(Node *p, unsigned int col);
void placeChip(Node *p, unsigned int col, char player);
int ColumnIsFree(Node *p, int col);
void move(Node *p, char player);

#endif