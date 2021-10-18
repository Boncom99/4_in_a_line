#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "minimax.h"
#include "print.h"
int player_computer = 2;
int player_human = 1;

void initializeNode(Node *p)
{
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
void copyBoard(Node *board1, Node *board2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            (board1)->board[i][j] = board2->board[i][j];
        }
    }
}
void showNode(Node *p, int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("-  %.6g (%d)\n", p->value, level);
}

void walkTreeRec(Node *root, int level)
{
    showNode(root, level);
    for (int i = 0; i < root->n_child; i++)
    {
        walkTreeRec(root->child[i], level + 1);
    }
}

void freeLevel(Node *father)
{
    free(father->child);
}
void freeTree(Node *root)
{
    for (int i = 0; i < root->n_child; i++)
    {
        freeTree(root->child[i]);
    }
    freeLevel(root);
}

Node *createNode(Node *father, int col, int level)
{
    char player = 1;
    if (level % 2) //level impar és pc
        player = 2;
    Node *p = (Node *)malloc(sizeof(Node));
    copyBoard(p, father);
    int row = fall(p, col);
    placeChip(p, row, col, player);
    score(p, row, col, player);
    if (player == 2)
    {
        p->value = p->value + (LEVEL - level); //perque guanyi abans
    }
    else if (player == 1)
    {
        p->value = p->value - (LEVEL - level); //perque guanyi abans
    }
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
        if (breakTreeOptimization(root->child[i], level))
        {
            change_num_child(root, i + 1);
            break;
        }
        else
            createTree(root->child[i], level + 1);
    }
}
int breakTreeOptimization(Node *p, int level) //checks if there is a MAX when its a pc's move, or if there is a MIN when it's the player's move.
{
    if (p->value == MIN && !(level % 2)) // pcmove
    {
        return 1;
    }
    else if (p->value == MAX && (level % 2))
    {
        return 1;
    }
    return 0;
}
void change_num_child(Node *p, int n_child)
{
    p->n_child = n_child;
}
void score(Node *p, int row, int col, int player)
{
    if (win(p, player, row, col))
    {
        if (player == 1) //Human
        {
            p->value = MIN;
        }
        else if (player == 2) //computer
        {
            p->value = MAX;
        }
    }
    else
    {
        p->value = rand() % 100 - 50;
    }
}
void min(Node *p)
{
    double aux = MAX;
    double current_value;
    for (int i = 0; i < p->n_child; i++)
    {
        current_value = p->child[i]->value;
        if (current_value < aux)
        {
            aux = current_value;
        }
    }
    p->value = aux;
}
void max(Node *p)
{
    double aux = MIN;
    double current_value;
    for (int i = 0; i < p->n_child; i++)
    {
        current_value = p->child[i]->value;
        if (current_value > aux)
        {
            aux = current_value;
        }
    }
    p->value = aux;
}
void minMax(Node *p, int level)
{
    for (int i = 0; i < p->n_child; i++)
    {
        minMax(p->child[i], level + 1);
    }
    if (p->n_child != 0) //per evitar que els nodes fulla apliquin el minmax
    {
        if (level % 2) //huma
            min(p);
        else
            max(p);
    }
}
int chooseColumn(Node *p)
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
int pcMove(Node *root)
{
    calculateNumChilds(root);
    root->child = malloc(root->n_child * sizeof(Node *));
    root->value = 0;
    createTree(root, 1);
    minMax(root, 0);
    //walkTreeRec(root, 0);
    freeTree(root);
    return chooseColumn(root);
}
