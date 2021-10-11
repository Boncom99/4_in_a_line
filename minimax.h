#define N 8
#define LEVEL 7
#define MAX 1000.0  //score if wins
#define MIN -1000.0 //score if loses
#ifndef MINIMAX_H
#define MINIMAX_H
#include "main.h"
#include "node.h"

void printNode(Node *p);
void initializeNode(Node *p);
void calculateNumChilds(Node *b);
void copyBoard(Node *board1, Node *board2);
void showNode(Node *p, int level);
void showLevel(Node *father, int level);
void walkTreeRec(Node *root, int level);
void freeNode(Node *p);
void freeLevel(Node *father);
void freeTree(Node *root);
Node *createNode(Node *father, int col, int level);
void createLevel(Node *father, int level);
void createTree(Node *root, int level);
int breakTreeOptimization(Node *p, int level); //checks if there is a MAX when its a pc's move, or if there is a MIN when it's the player's move.
void change_num_child(Node *p, int n_child);
void score(Node *p, int row, int col, int player);
void min(Node *p);
void max(Node *p);
void minMax(Node *p, int level);
int chooseColumn(Node *p);
int pcMove(Node *old);

#endif
