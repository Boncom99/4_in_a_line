#define N 4
#define LEVEL 4
#define MAX 1000.0 //score if wins
#define MIN -500.0 //score if loses
#ifndef MINIMAX_H
#define MINIMAX_H
#include "4enralla.h"
#include "node.h"

void printNode(Node *p);
void initializeNode(Node *p);
void calculateNumChilds(Node *b);
void copyBoard(Node **board1, Node *board2);
void showNode(Node *p, int level);
void showLevel(Node *father, int level);
void walkTreeRec(Node *root, int level);
void walkTree(Node *root);
void freeNode(Node *p);
void freeLevel(Node *father);
void freeTree(Node *root);
Node *createNode(Node *father, int n_of_child, int level);
void createLevel(Node *father, int level);
void createTree(Node *root, int level);
void Score(Node *p);
void min(Node *p);
void max(Node *p);
void minMax(Node *p, int level);
int chooseColumn(Node *p);
int pcMove(Node *old);

#endif