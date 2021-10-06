#include <stdio.h>
#include <stdlib.h>
#include "4enralla.h"
#include "minimax.h"
#include "print.h"

int askMove()
{
    int aux = 0;
    do
    {
        printf("what columns do you want to play?(1,2,3,4,5,6,7,8)\n");
        scanf("%d", &aux);
    } while (aux > N || aux < 0);

    return aux - 1;
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
int win(Node *p)
{
    int horitzontal = 0;
    int vertical = 0;
    for (int i = 0; i < N; i++)
    {
        horitzontal = checkHorizontal(p, p->board[N - i - 1][0], i, 0, 0);
        vertical = checkVertical(p, p->board[0][i], 0, i, 0);
        if (horitzontal != 0)
        {
            return (int)horitzontal;
        }
        else if (vertical != 0)
        {
            return (int)vertical;
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
    if (aux != 0)
    {
        printf("\n  GAME OVER \n The board is full! \n ");
        return 1;
    }
    return 0;
}
char finish(Node *p)
{
    printf(" \n alkfjalflasf \n");
    int aux = win(p);
    printf("\n aaaaaaaaa   %d\n", aux);
    if (aux != 0)
    {
        printf("\n WINS THE PLAYER %d! \n\n", aux);
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
void placeChip(Node *p, unsigned int col, char player)
{
    int row = fall(p, col);
    p->board[row][col] = player;
}
int ColumnIsFree(Node *p, int col)
{
    if (p->board[0][col] == 0)
    {
        return 1;
    }
    return 0;
}

void move(Node *p, char player)
{
    unsigned int col;
    do
    {
        col = askMove();

    } while (!ColumnIsFree(p, col));
    placeChip(p, col, player);
    printBoard(p->board);
}
int main()
{
    Node p;
    initializeBoard(&p);
    printBoard(p.board);
    char player = 1;
    while (!finish(&p))
    {
        move(&p, player);
        player = (player % 2) + 1;
    }
    return 0;
}