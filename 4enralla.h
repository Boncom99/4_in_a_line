#ifndef ENRALLA_H
#define ENRALLA_H
#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"

#define N 8
#define LEVEL 4

typedef struct node
{
    char board[N][N];
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
void showNode(Node *p, int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("-  %f\n", p->value);
}
void showLevel(Node *father, int level)
{
    for (int i = 0; i < father->n_child; i++)
    {
        showNode(father->child[i], level);
    }
}
void walkTree(Node *root)
{
    showLevel(root, 1);
    for (int i = 0; i < arrel->n_child; i++)
    {
        showLevel(root->child[i], 2);
    }
}
Node *createNode(Node *father, int n_of_child, int level)
{
    Node *p = (Node *)malloc(sizeof(Node));
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

    createLevel(root, 1);
    for (int i = 0; i < root->n_child; i++)
    {
        createLevel(root->child[i], 2);
    }
}
void initializeBoard(Node *p)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            p->board[i][j] = 0;
            //p->board[i][j] = rand() % 2 + 1;
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
int estaFora(int row, int col)
{

    if (row >= N || col >= N || row < 0 || col < 0)
    {
        return 1;
    }
    return 0;
}
int checkHorizontal(Node *p, int player, int row, int col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        printf(" WIN player %d!\n", player);
        return player;
    }
    if (!estaFora(row, col))
    {

        int player_in_position = p->board[row][col];
        if (player_in_position == player && player_in_position != 0)
        {
            aux = checkHorizontal(p, player_in_position, row, col + 1, count + 1);
        }
        else
        {
            aux = checkHorizontal(p, player_in_position, row, col + 1, 0);
        }
    }
    return aux;
}

int checkVertical(Node *p, int player, int row, int col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        printf(" WIN player %d!\n", player);
        return player;
    }
    if (!estaFora(row, col))
    {

        int player_in_position = p->board[row][col];
        if (player_in_position == player)
        {
            aux = checkHorizontal(p, player_in_position, row + 1, col, count + 1);
        }
        else
        {
            aux = checkHorizontal(p, player_in_position, row + 1, col, 0);
        }
    }
    return aux;
}
char win(Node *p)
{
    int aux_h = 0;
    int aux_v = 0;
    for (int i = 0; i < N; i++)
    {
        aux_h = checkHorizontal(p, p->board[N - i - 1][0], i, 0, 0);
        aux_v = checkVertical(p, p->board[0][i], 0, i, 0);
        if (aux_h != 0)
        {
            return aux_h;
        }
        else if (aux_v != 0)
        {
            return aux_h;
        }
    }
    return 0;
}
int isFull(Node *p)
{
    int aux = 1;
    for (int i = 0; i < N; i++)
    {
        aux *= p->board[0][i];
    }
    return aux;
}
char finish(Node *p)
{
    char aux = win(p);
    if (aux != 0)
    {
        return aux;
    }
    else if (isFull(p))
    {
        return 3;
    }
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
void placeChip(Node *p, unsigned int row, unsigned int col, char player)
{
    p->board[row][col] = player;
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
    placeChip(p, row, col, player);
    printBoard(p->board);
}

#endif