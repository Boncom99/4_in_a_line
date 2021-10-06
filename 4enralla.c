
#include "4enralla.h"

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