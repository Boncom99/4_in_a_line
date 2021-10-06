#include <stdio.h>
#include <stdlib.h>
#define N 4
#define LEVEL 3
int counter = 0;
typedef struct node
{
    char board[N][N];
    struct node **child;
    int n_child;
    double value;
} Node;
int calculateNumChilds(Node *b)
{
    int aux = 0;
    for (int i = 0; i < N; i++)
    {
        if (b->board[0][i] == 0)
        {
            aux++;
        }
    }
    return aux;
}
void copyBoard(Node **board1, Node *board2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            (*board1)->board[i][j] = board2->board[i][j];
        }
    }
}
void showNode(Node *p, int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("-  %f\n", p->value);
}
void showLevel(Node *father, int level)
{
    for (int i = 0; i < father->n_child; i++)
    {
        showNode(father->child[i], level);
    }
}
void walkTreeRec(Node *root, int level)
{
    showNode(root, level);

    for (int i = 0; i < root->n_child; i++)
    {
        walkTreeRec(root->child[i], level + 1);
    }
}
void walkTree(Node *root)
{
    showLevel(root, 1);
    for (int i = 0; i < root->n_child; i++)
    {
        showLevel(root->child[i], 2);
    }
}
Node *createNode(Node *father, int n_of_child, int level)
{
    Node *p = (Node *)malloc(sizeof(Node));
    copyBoard(&p, father);
    doMove(p->board, int n_of_Child);
    if (level < 2)
    {
        p->n_child = calculateNumChilds(p);
        p->child = malloc(p->n_child * sizeof(Node *));
    }
    else
    {
        p->n_child = 0;
        p->child = NULL;
    }
    p->value = counter;
    counter++;
    return p;
}
void createLevel(Node *father, int level)
{
    for (int i = 0; i < father->n_child; i++)
    {
        father->child[i] = createNode(father, i, level);
    }
}
void createTree(Node *root)
{

    createLevel(root, 1);
    for (int i = 0; i < root->n_child; i++)
    {
        createLevel(root->child[i], 2);
    }
}
void initializeBoard(Node *p)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            p->board[i][j] = 0;
            //p->board[i][j] = rand() % 2 + 1;
        }
    }
}
int main()
{
    Node *root = malloc(sizeof(Node));
    root->n_child = N;
    root->value = 100;
    root->child = malloc(root->n_child * sizeof(Node *));
    createTree(root);
    walkTreeRec(root, 0);
    return 0;
}