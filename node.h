#ifndef NODE_H
#define NODE_H
typedef struct node
{
    char board[N][N];
    struct node **child;
    int n_child;
    double value;
} Node;
#endif