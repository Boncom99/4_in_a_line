#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"
#include "main.h"
void newGame(int Points[2])
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("%s  %d  -  %d  COMPUTER\n\n", name, Points[0], Points[1]);

    printf("Good luck %s! \n\n", name);
}
int playAgain()
{
    char aux = '\0';
    printf("\n %s do you want to play again? (y/n) \n", name);
    do
    {
        scanf("%c", &aux);
        if (aux == 'y')
        {
            return 1;
        }
        else if (aux == 'n')
        {
            return 0;
        }
        //printf("I didn't understand what you said! %s do you want to play again? (y/n)", name);
    } while (1);
}
void askForName(char *a)
{
    printf("Players 1 name: ");
    scanf("%s", a);
    printf("\n");
}
void printLine()
{
    printf("\n   ");
    for (int k = 0; k < N; k++)
    {
        printf("____  ");
    }
    printf("\n  ");
}
void printNumbers()
{
    printf("   ");

    for (int k = 0; k < N; k++)
    {
        printf("  %d   ", k + 1);
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
                printf("| 🟡 |");
            }
            else if (b[i][j] == 2)
            {
                printf("| 🟦 |");
            }
            else
            {
                printf("|    |");
            }
        }
    }
    printLine();
    printf("\n");
}