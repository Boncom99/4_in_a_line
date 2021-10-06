#ifndef NODE_H
#define NODE_H
typedef struct node
{
    char board[N][N];
    struct node **child;
    int available_cols[N]; //vector contains the column in which each child has to do the move (and then fill with (-1)).
    int n_child;
    double value;
} Node;
#endif