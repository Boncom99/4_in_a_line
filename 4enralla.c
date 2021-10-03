
#include "4enralla.h"

int main()
{
    Node p;
    initializeBoard(&p);
    printBoard(p.board);
    char player = 0;
    while (!finish())
    {
        move(&p, player);
        player++;
        player = player % 2;
    }
    return 0;
}