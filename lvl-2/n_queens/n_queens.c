#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int issafe(int *board, int row, int col)
{
    int i = 0;
    while(i < col)
    {
        if (board[i] == row) return 0;
        else if (board[i] + i == col + row) return 0;
        else if (board[i] - i == row - col) return 0;
        i++;
    }
    return 1;
}

void printsol(int *board, int n)
{
    int i = 0;
    while(i < n)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < n-1) fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
}


void solve(int *board, int col, int n)
{
    if (col == n)
    {
        printsol(board, n);
        return ;
    }
    int row = 0;
    while(row < n)
    {
        if(issafe(board, row, col))
        {
            board[col] = row;
            solve(board, col + 1, n);
        }
        row++;
    }
}


int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
       
    int n = atoi(argv[1]);
    if (n < 1)
        return 0;
    int *board = (int *)malloc(sizeof(int) * n);
    if(!board)
    {
        fprintf(stderr, "malloc");
        return 1;
    }
    solve(board, 0, n);
   
    free(board);
    return 0;
}