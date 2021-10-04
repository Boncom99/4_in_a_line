#ifndef ENRALLA_H
#define ENRALLA_H
#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"

#define N 8
#define LEVEL 4

typedef struct node
{
    char board[N][N]; //1 byte onlys
    struct node **child;
    int n_child;
    double value;
} Node;
int calculateNumChilds(Node *b)
{
    int aux = 0;
    for (int i = 0; i < N; i++)
    {
        if (b->board[0][i] == 0)
        {
            aux++;
        }
    }
    return aux;
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
Node *createNode(Node *father, int n_of_child, int level)
{
    Node *p = malloc(sizeof(Node));
    copyBoard(&p, father);
    // move(p->board, int n_of_child);
    if (level < LEVEL)
    {
        p->n_child = calculateNumChilds(p);
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
        father->child[i] = createNode(father, i, level);
    }
}
void createTree(Node *root)
{

    createLevel(root, LEVEL);
    for (int i = 0; i < root->n_child; i++)
    {
        createLevel(root->child[i], LEVEL);
    }
}
void initializeBoard(Node *p)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            p->board[i][j] = 0;
        }
    }
}
void printLine()
{
    printf("\n   ");
    for (int k = 0; k < N; k++)
    {
        printf("___  ");
    }
    printf("\n  ");
}
void printNumbers()
{
    printf("  ");

    for (int k = 0; k < N; k++)
    {
        printf("  %d  ", k + 1);
    }
}
void printBoard(char b[N][N])
{
    printNumbers();
    for (int i = 0; i < N; i++)
    {

        printLine();
        for (int j = 0; j < N; j++)
        {
            // printf("|%d %d|", i, j);
            if (b[i][j] == 1)
            {
                printf("| ✘ |");
            }
            else if (b[i][j] == 2)
            {
                printf("| ○ |");
            }
            else
            {
                printf("|   |");
            }
        }
    }
    printLine();
}
void askMove(unsigned int *move)
{
    int aux = 0;
    do
    {
        printf("what columns do you want to play?(1,2,3,4,5,6,7,8)\n");
        scanf("%d", &aux);
    } while (aux > N || aux < 0);

    *move = aux - 1;
}
int finish()
{
    return 0;
}
unsigned int fall(Node *p, unsigned int col)
{
    unsigned int row = N - 1;
    for (int i = 0; i < N; i++)
    {
        if (p->board[i][col] != 0)
        {
            row = i - 1;
            break;
        }
    }
    return row;
}
void placeChip(Node *p, unsigned int col, unsigned int row, char player)
{
    p->board[row][col] = player + 1;
}
char *checkColumns(Node *p)
{
    char *cols = (char *)malloc(N * sizeof(char)); //si no fessim malloc al acabar la funció es borraria la v.
    for (int i = 0; i < N; i++)
    {
        if (p->board[0][i] == 0)
        {
            cols[i] = 0;
        }
        else
        {
            cols[i] = 1;
        }
    }
    return cols;
}

void move(Node *p, char player)
{
    unsigned int col;
    unsigned int row;
    char *columns;
    columns = checkColumns(p);
    do
    {
        askMove(&col);
    } while (columns[col] != 0);
    free(columns);
    row = fall(p, col);
    placeChip(p, col, row, player);
    printBoard(p->board);
}

#endif