#ifndef MAIN_H
#define MAIN_H
#include "minimax.h"
#include "node.h"
char name[20];

int askMove();
int isOutside(int row, int col);
int checkHorizontal(Node *p, int player, int row, int col, int last_col, int count);
int checkVertical(Node *p, int player, int row, int col, int last_row, int count);
int checkAscendentDiagonal(Node *p, int player, int row, int col, int last_row, int count);
int checkDescendentDiagonal(Node *p, int player, int row, int col, int last_row, int count);
int win(Node *p, int player, int row, int col);
int isFull(Node *p);
char finish(Node *p, int player, int row, int col);
unsigned int fall(Node *p, unsigned int col);
void placeChip(Node *p, unsigned int row, unsigned int col, int player);
int ColumnIsFree(Node *p, int col);
int *move(Node *p, int player);
int humanMove(Node *p);

#endif