#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "minimaxOLD.h"
#include "print.h"

int askMove()
{
    int aux = 0;
    do
    {
        printf(" turn to move 🟡 %s 🟡! what columns do you want to play?\n", name);
        for (int i = 1; i <= N; i++)
        {
            printf(" %d ", i);
        }
        printf("\n");

        scanf("%d", &aux);
        printf("\n");
    } while (aux > N || aux < 0);

    return aux - 1;
}
int isOutside(int row, int col)
{

    if (row >= N || col >= N || row < 0 || col < 0)
    {
        return 1;
    }
    return 0;
}
int checkHorizontal(Node *p, int player, int row, int col, int last_col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (col <= last_col)
    {

        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkHorizontal(p, player, row, col + 1, last_col, count + 1);
        }
        else
        {
            aux = checkHorizontal(p, player, row, col + 1, last_col, 0);
        }
    }
    return aux;
}
int checkVertical(Node *p, int player, int row, int col, int last_row, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (row <= last_row)
    {
        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkVertical(p, player, row + 1, col, last_row, count + 1);
        }
        else
        {
            aux = checkVertical(p, player, row + 1, col, last_row, 0);
        }
    }
    return aux;
}
int checkDescendentDiagonal(Node *p, int player, int row, int col, int last_row, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (!isOutside(row, col) && row <= last_row)
    {

        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkDescendentDiagonal(p, player, row + 1, col + 1, last_row, count + 1);
        }
        else
        {
            aux = checkDescendentDiagonal(p, player, row + 1, col + 1, last_row, 0);
        }
    }
    return aux;
}
int checkAscendentDiagonal(Node *p, int player, int row, int col, int last_row, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (!isOutside(row, col) && row <= last_row)
    {

        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkAscendentDiagonal(p, player, row - 1, col + 1, last_row, count + 1);
        }
        else
        {
            aux = checkAscendentDiagonal(p, player, row - 1, col + 1, last_row, 0);
        }
    }
    return aux;
}

int start_row(int row, int col)
{
    while (isOutside(row - 3, col))
    {

        row++;
    }
    return row - 3;
}
int end_row(int row, int col)
{
    while (isOutside(row + 3, col))
    {

        row--;
    }
    return row + 3;
}
int start_col(int row, int col)
{
    while (isOutside(row, col - 3))
    {

        col++;
    }
    return col - 3;
}
int end_col(int row, int col)
{
    while (isOutside(row, col + 3))
    {

        col--;
    }
    return col + 3;
}
int *diagonalTopLeft(int row, int col)
{
    while (isOutside(row - 3, col - 3))
    {
        row++;
        col++;
    }
    static int v[2];
    v[0] = row - 3;
    v[1] = col - 3;
    return v;
}

int *diagonalBottomLeft(int row, int col)
{

    while (isOutside(row + 3, col - 3))
    {
        row--;
        col++;
    }
    static int v[2];
    v[0] = row + 3;
    v[1] = col - 3;
    return v;
}

int win(Node *p, int player, int row, int col)
{ //calculate the margins where a 4 in line can be found given the last play (row,col)
    int row0 = start_row(row, col);
    int row1 = end_row(row, col);
    int col0 = start_col(row, col);
    int col1 = end_col(row, col);
    int *topLeft = diagonalTopLeft(row, col);
    int *bottomLeft = diagonalBottomLeft(row, col);

    //Horizontal
    if (checkHorizontal(p, player, row, col0, col1, 0))
    {
        return 1;
    }
    //vertical

    if (checkVertical(p, player, row0, col, row1, 0))
    {
        return 1;
    }
    //diagonals

    if (checkAscendentDiagonal(p, player, bottomLeft[0], bottomLeft[1], row1, 0))
    {
        return 1;
    }

    if (checkDescendentDiagonal(p, player, topLeft[0], topLeft[1], row1, 0))
    {
        return 1;
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
char finish(Node *p, int player, int row, int col)
{
    if (win(p, player, row, col))
    {
        if (player == 2)
            printf("\n 🥳🎉🦾🦾THE COMPUTER HAS WON! 🥳🎉\n\n");
        else
            printf("\n 🥳🎉💪CONGRATULATIONS %s! YOU HAVE WON ! 🥳🎉\n\n", name);
        return 1;
    }
    else if (isFull(p))
    {
        return 1;
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
void placeChip(Node *p, unsigned int row, unsigned int col, int player)
{
    p->board[row][col] = (char)player;
}
int ColumnIsFree(Node *p, int col)
{
    if (p->board[0][col] == 0)
    {
        return 1;
    }
    return 0;
}
int humanMove(Node *p)
{
    unsigned int col;
    do
    {
        col = askMove();

    } while (!ColumnIsFree(p, col));
    return col;
};
int *move(Node *p, int player)
{
    unsigned int col;
    if (player % 2) //HUMA;
    {
        //col = humanMove(p);
       col = pcMoveOLD(p);
    }
    else
    {
        col = pcMove(p);
    }
    int row = fall(p, col);
    placeChip(p, row, col, player);
    printBoard(p->board);
    static int v[2];
    v[0] = row;
    v[1] = col;

    return v;
}
int main()
{

    askForName(name);
    Node MAIN;
    int Points[2] = {0, 0};
    int *movement;
    do
    {
        newGame(Points);
        initializeNode(&MAIN);
        printBoard(MAIN.board);
        int player = 2;
        do
        {
            player = (player % 2) + 1;
            movement = move(&MAIN, player);
        } while (!finish(&MAIN, player, movement[0], movement[1]));
        Points[player - 1]++;

    } while (playAgain());
    return 0;
}
