#ifndef ENRALLA_H
#define ENRALLA_H
#include "minimax.h"
#include "node.h"
int askMove();
int isOutside(int row, int col);
int checkHorizontal(Node *p, int player, int row, int col, int count);
int checkVertical(Node *p, int player, int row, int col, int count);
int checkAscendentDiagonal(Node *p, int player, int row, int col, int count);
int checkDescendentDiagonal(Node *p, int player, int row, int col, int count);
int win(Node *p, int player);
int isFull(Node *p);
char finish(Node *p, int player);
unsigned int fall(Node *p, unsigned int col);
void placeChip(Node *p, unsigned int col, int player);
int ColumnIsFree(Node *p, int col);
void move(Node *p, int player);
int humanMove(Node *p);

#endif