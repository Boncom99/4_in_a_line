#define N 8
#define LEVEL 3
#ifndef MINIMAX_H
#define MINIMAX_H
#include "4enralla.h"
#include "node.h"

void calculateNumChilds(Node *b);

void copyBoard(Node **board1, Node *board2);

void showNode(Node *p, int level);

void showLevel(Node *father, int level);

void walkTreeRec(Node *root, int level);

void walkTree(Node *root);

Node *createNode(Node *father, int n_of_child, int level);

void createLevel(Node *father, int level);

void createTree(Node *root);

void initializeNode(Node *p);

#endif