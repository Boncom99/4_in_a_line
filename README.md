To compile the game run:

        gcc -Wall -g -std=c11 4enralla.c minimax.c print.c -o main

then, to play run:

        ./main


SETTINGS:

    To change the board size go to minimax.h, line 1 and change the variable N.
    To change the number of levels that the MINIMAX algorithm uses go to minimax.h, line 2 and change the variable LEVEL.

IMPLEMENTATIONS:

    - MINIMAX optimization:

        Instead of creating the Tree and then evaluating the leaf nodes, what the program does is evaluate every node when is created, and if it gets a score of MAX (Wins) or MIN (Loses), then stops creating more children from them. And then apply the MINIMAX algorithm with the remaining tree.
        this way the number of nodes will get reduced.

        It is an approach of the Alpha-Beta optimizations, but, because my score() function only returns MIN, MAX, or rand(), it would be stupid to compare scores that are randomly generated.

    - Name of the player:
        
         Before starting the game, the program asks for the player's name, this way, Him/ Her will feel more related to the game and more involved.




Have fun playing!👍

        