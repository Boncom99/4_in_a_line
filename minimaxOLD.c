#include "minimaxOLD.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "print.h"
Node *createNodeOLD(Node *father, int col, int level)
{
    char player = 1;
    if (level % 2) //level impar és pc
        player = 2;
    Node *p = (Node *)malloc(sizeof(Node));
    copyBoard(p, father);
    int row = fall(p, col);
    placeChip(p, row, col, player);
    scoreOLD(p, row, col, player, level);
    if (level < LEVEL && p->value < MAX && p->value > MIN) //Si una jugada guanya o perd ja no fem més fills d'aquella branca
    {
        calculateNumChilds(p);
        p->child = malloc(p->n_child * sizeof(Node *));
    }
    else
    {
        p->n_child = 0;
        p->child = NULL;
    }
    return p;
}
void scoreOLD(Node *p, int row, int col, int player, int level)
{
    if (win(p, player, row, col))
    {
        if (player == 1) //Human
        {
            p->value = MIN - (LEVEL - level);
            ;
        }
        else if (player == 2) //computer
        {
            p->value = MAX + (LEVEL - level);
            ;
        }
    }
    else
    {
        p->value = rand() % 100 - 50;
    }
}

int chooseColumnOld(Node *p)
{
    for (int i = 0; i < p->n_child; i++)
    {
        if (p->value == p->child[i]->value)
        {
            return p->available_cols[i];
        }
    }
    return 0;
}
void createLevelOLD(Node *father, int level)
{
    for (int i = 0; i < father->n_child; i++)
    {
        father->child[i] = createNodeOLD(father, father->available_cols[i], level);
    }
}
void createTreeOLD(Node *root, int level)
{

    createLevelOLD(root, level);
    for (int i = 0; i < root->n_child; i++)
    {
        if (breakTreeOptimization(root->child[i], level))
        {
            change_num_child(root, i + 1);
            break;
        }
        else
            createTreeOLD(root->child[i], level + 1);
    }
}
int pcMoveOLD(Node *input)
{
    Node *root = (Node *)malloc(sizeof(Node));
    copyBoard(root, input);
    calculateNumChilds(root);
    root->child = malloc(root->n_child * sizeof(Node *));
    root->value = 0;
    createTreeOLD(root, 1);
    minMax(root, 0);
    //walkTreeRec(root, 0);
    int col = chooseColumnOld(root);
    freeTree(root);
    return col;
}
