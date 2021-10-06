#include <stdio.h>
#include <stdlib.h>
#include "4enralla.h"
#include "minimax.h"

int counter = 0;
void initializeNode(Node *p)
{ //board
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            p->board[i][j] = 0;
        }
        p->available_cols[i] = 1;
    }
}
void calculateNumChilds(Node *b)
{

    int aux = 0;
    for (int i = 0; i < N; i++)
    {
        if (b->board[0][i] == 0)
        {
            b->available_cols[aux] = i;
            aux++;
        }
    }
    for (int i = aux + 1; i < N; i++) //fill the rest of the vector with (-1)
    {
        b->available_cols[i] = -1;
    }
    b->n_child = aux;
}
void copyBoard(Node **board1, Node *board2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            (*board1)->board[i][j] = board2->board[i][j];
        }
    }
}
void showNode(Node *p, int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("-  %.6g\n", p->value);
}
void showLevel(Node *father, int level)
{
    for (int i = 0; i < father->n_child; i++)
    {
        showNode(father->child[i], level);
    }
}
void walkTreeRec(Node *root, int level)
{
    showNode(root, level);

    for (int i = 0; i < root->n_child; i++)
    {
        walkTreeRec(root->child[i], level + 1);
    }
}
void walkTree(Node *root)
{
    showLevel(root, 1);
    for (int i = 0; i < root->n_child; i++)
    {
        showLevel(root->child[i], 2);
    }
}
void freeNode(Node *p)
{
    free(p);
}
void freeLevel(Node *father)
{
    for (int i = 0; i < father->n_child; i++)
    {
        freeNode(father->child[i]);
    }
    freeNode(father);
}

void freeTree(Node *root)
{
    for (int i = 0; i < root->n_child; i++)
    {
        freeTree(root->child[i]);
    }
    freeLevel(root);
}
Node *createNode(Node *father, int n_of_col, int level)
{
    Node *p = (Node *)malloc(sizeof(Node));
    copyBoard(&p, father);
    placeChip(p, n_of_col, 2); //TODO change 2
    if (level < LEVEL)
    {
        calculateNumChilds(p);
        p->child = malloc(p->n_child * sizeof(Node *));
    }
    else
    {
        p->n_child = 0;
        p->child = NULL;
    }
    p->value = counter;
    counter++;
    return p;
}
void createLevel(Node *father, int level)
{
    for (int i = 0; i < father->n_child; i++)
    {
        father->child[i] = createNode(father, father->available_cols[i], level);
    }
}
void createTree(Node *root, int level)
{

    createLevel(root, level);
    for (int i = 0; i < root->n_child; i++)
    {
        createTree(root->child[i], level + 1);
    }
}

int main()
{
    Node *root = malloc(sizeof(Node));
    root->n_child = N;
    initializeNode(root);
    root->value = 100;
    root->child = malloc(root->n_child * sizeof(Node *));
    createTree(root, 1);
    freeTree(root);

    //walkTreeRec(root, 0);
    return 0;
}
