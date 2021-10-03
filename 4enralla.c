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
            p->board[i][j] = rand() % 3;
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
void printBoard(char b[N][N])
{

    for (int i = 0; i < N; i++)
    {

        printLine();
        for (int j = 0; j < N; j++)
        {

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
void askMove(int *move)
{
    printf("what columns do you want to play?(0,1,2,3,4,5,6,7)\n");
    scanf("%d", move);
}
int main()
{
    Node p;
    initializeBoard(&p);
    printBoard(p.board);
    int a;
    askMove(&a);
    return 0;
}