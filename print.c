#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"
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
    printf("\n");
}