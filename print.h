#ifndef PRINT_H
#define PRINT_H
#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"
void newGame(int Points[2]);
int playAgain();
void askForName(char *a);
void printLine();
void printNumbers();
void printBoard(char b[N][N]);
#endif