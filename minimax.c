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
    free(father);
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
    score(p, row, col, player, level);
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
    if (p->value <= MIN && !(level % 2)) // pcmove
    {
        return 1;
    }
    else if (p->value >= MAX && (level % 2))
    {
        return 1;
    }
    return 0;
}
void change_num_child(Node *p, int n_child)
{
    p->n_child = n_child;
}
int probabilisticScore(Node *p, int row, int col){
    int points[8] = {1, 2, 3, 4, 4, 3, 2, 1};
    return (points[col]);
}

void score(Node *p, int row, int col, int player, int level)
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
        int aux = (player % 2);
        p->value = (-2*aux + 1 )* probabilisticScore(p, row, col); //if player is "1" we multiply by "-1". if player is 2 it stays the same
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
    int points[8] = {1, 2, 3, 4, 4, 3, 2, 1};
    int bestCols[8]={0,0,0,0,0,0,0,0};
    for (int i = 0; i < p->n_child; i++)
    {
        if (p->value == p->child[i]->value)
        {
            bestCols[p->available_cols[i]] = 1; //save a 1 in every columns that gets the maximum puntuation.
        }
    }
    int max = -100;
    int col = -1;
    //printf("best cols-> ");
    for (int i = 0; i < 8; i++) //now we get the most centered column with max puntiation
    {
        if (bestCols[i] == 1)
        {
            //printf("%d, ", i);
            int row = fall(p, i);
            if (4 * points[i] + points[row] > max)
            {
            //printf("(%d,%d )", row, 4 * points[i] + points[row]);
                max = 4 * points[i] + points[row];
                col = i;
            }
        }
    }
    //printf("\n");
    
    return col;
}
int pcMove(Node *input)
{
     Node *root = (Node *)malloc(sizeof(Node));
    copyBoard(root, input);
    calculateNumChilds(root);
    root->child = malloc(root->n_child * sizeof(Node *));
    root->value = 0;
    createTree(root, 1);
    minMax(root, 0);
    //walkTreeRec(root, 0);
    int col = chooseColumn(root);
    freeTree(root);
    return col;
}
