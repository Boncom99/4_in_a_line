To compile the game run:

        gcc -Wall -g -O3 -std=c11 main.c minimax.c print.c -o main

then, to play run:

        ./main


SETTINGS:

    To change the board size go to minimax.h, line 1 and change the variable N.
    To change the number of levels that the MINIMAX algorithm uses go to minimax.h, line 2 and change the variable LEVEL.

IMPLEMENTATIONS:

    - MINIMAX optimization 1 (in createNode()):

        Instead of creating the Tree and then evaluating the leaf nodes, what the program does is evaluate (with the function score()) every node when is created, and if it gets a score of MAX (Wins) or MIN (Loses), then stops creating more children from them. And then apply the MINIMAX algorithm with the remaining tree.
        This implementation can be interpreted as stoping the tree from spreading in those directions where the game is already over.
        this way the number of nodes will get reduced.

    -MINIMAX optimization 2 (in createtree()):

        The idea is to stop creating more "brothers" from one "father" if a child gives us the best move that the computer can make to win or to avoid the other player to win (depending on which level it is).

        
        With LEVEL = 8, we can perceive these two optimizations. In particular, in those plays where one of the players can win in the next move. in Those cases, the MINIMAX algorithm decides the next move in less than a second.
        It is an approach of the Alpha-Beta optimizations, but, because my score() function only returns MIN, MAX, or rand(), it would be stupid to compare scores that are randomly generated.

    - optimized win() function:

        because in the "minimax optimization 1" calls the win() function for every Node created, i have optimized the win() function.
        instead of checking all rows, columns, and diagonals, it only checks the row, column, and diagonals where the last chip has moved! it was a function whose number of operations was N^4 and now is 4. 
        (it is a really big upgrade if the board gets bigger)

    - Name of the player:
        
         Before starting the game, the program asks for the player's name, this way, Him/She will feel more related to the game and more involved.

    - Multiple matches:

        when the game is over, the program lets you play again, keeping the current score.



Have fun playing!👍

        