#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "minimax.h"
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
int checkHorizontal(Node *p, int player, int row, int col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (!isOutside(row, col))
    {

        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkHorizontal(p, player, row, col + 1, count + 1);
        }
        else
        {
            aux = checkHorizontal(p, player, row, col + 1, 0);
        }
    }
    return aux;
}
int checkDescendentDiagonal(Node *p, int player, int row, int col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (!isOutside(row, col))
    {

        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkDescendentDiagonal(p, player, row + 1, col + 1, count + 1);
        }
        else
        {
            aux = checkDescendentDiagonal(p, player, row + 1, col + 1, 0);
        }
    }
    return aux;
}
int checkAscendentDiagonal(Node *p, int player, int row, int col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (!isOutside(row, col))
    {

        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkAscendentDiagonal(p, player, row + 1, col - 1, count + 1);
        }
        else
        {
            aux = checkAscendentDiagonal(p, player, row + 1, col - 1, 0);
        }
    }
    return aux;
}
int checkVertical(Node *p, int player, int row, int col, int count)
{
    int aux = 0;
    if (count == 4)
    {
        return 1;
    }
    if (!isOutside(row, col))
    {
        int chip = p->board[row][col];
        if (chip == player && chip != 0)
        {
            aux = checkVertical(p, player, row + 1, col, count + 1);
        }
        else
        {
            aux = checkVertical(p, player, row + 1, col, 0);
        }
    }
    return aux;
}
int win(Node *p, int player)
{
    //vertical and Horitzontal
    for (int i = 0; i < N; i++)
    {

        if (checkHorizontal(p, player, N - 1 - i, 0, 0))
        {
            return 1;
        }
        else if (checkVertical(p, player, 0, i, 0))
        {
            return 1;
        }
    }
    //diagonals
    {

        for (int i = N - 4; i >= 0; i--) //diagonals starting from the side
        {
            if (checkAscendentDiagonal(p, player, i, N - 1, 0))
            {
                return 1;
            }
            else if (checkDescendentDiagonal(p, player, i, 0, 0))
            {
                return 1;
            }
        }
        for (int i = 1; i < N - 3; i++) //diagonals starting from the top (starting from 1 bc the main diagonal is already checked)
        {
            if (checkAscendentDiagonal(p, player, 0, N - 1 - i, 0))
            {
                return 1;
            }
            else if (checkDescendentDiagonal(p, player, 0, i, 0))
            {
                return 1;
            }
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
char finish(Node *p, int player)
{
    if (win(p, player))
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
void placeChip(Node *p, unsigned int col, int player)
{
    int row = fall(p, col);
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
void move(Node *p, int player)
{
    unsigned int col;
    if (player % 2) //HUMA;
    {
        col = humanMove(p);
    }
    else
    {
        col = pcMove(p);
    }
    placeChip(p, col, player);
    printBoard(p->board);
}
int main()
{

    askForName(name);
    Node MAIN;
    int Points[2] = {0, 0};

    do
    {
        newGame(Points);
        initializeNode(&MAIN);
        printBoard(MAIN.board);
        int player = 2;
        do
        {
            player = (player % 2) + 1;
            move(&MAIN, player);
        } while (!finish(&MAIN, player));
        Points[player - 1]++;

    } while (playAgain());
    return 0;
}