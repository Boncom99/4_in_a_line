#ifndef MAIN_H
#define MAIN_H
#include "minimax.h"
#include "node.h"
char name[20];

int askMove();
int isOutside(int row, int col);                                                     //check if the position is ouside the board
int checkHorizontal(Node *p, int player, int row, int col, int last_col, int count); //checks horizontal's 4_in_line.
int checkVertical(Node *p, int player, int row, int col, int last_row, int count);
int checkAscendentDiagonal(Node *p, int player, int row, int col, int last_row, int count);
int checkDescendentDiagonal(Node *p, int player, int row, int col, int last_row, int count);
int start_row(int row, int col); //define in which row we have to start checking if there is a win
int end_row(int row, int col);   //define in which row we have to stop checking if there is a win
int start_col(int row, int col);
int end_col(int row, int col);
int *diagonalTopLeft(int row, int col);
int *diagonalBottomLeft(int row, int col);
int win(Node *p, int player, int row, int col);
int isFull(Node *p);
char finish(Node *p, int player, int row, int col);
unsigned int fall(Node *p, unsigned int col);
void placeChip(Node *p, unsigned int row, unsigned int col, int player);
int ColumnIsFree(Node *p, int col);
int *move(Node *p, int player);
int humanMove(Node *p);

#endif