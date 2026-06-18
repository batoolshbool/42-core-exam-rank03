#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printsol(int *subset, int n)
{
    int i = 0;
    while(i < n)
    {
        fprintf(stdout, "%d", subset[i]);
        if(i < n- 1) fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
}

void solve(int *set, int n, int target, int index, int sum, int *subset, int subnum)
{
    if(index == n)
    {
        if(sum == target) printsol(subset, subnum);
        return ;
    }
   
    solve(set, n, target, index + 1, sum, subset, subnum);
   
    subset[subnum] = set[index];
    solve(set, n, target, index + 1, sum + set[index], subset, subnum + 1);
}

int main(int argc, char **argv)
{
    if(argc < 3) return 1;
   
    int target = atoi(argv[1]);
    int n = argc - 2;
    int *set = malloc(sizeof(int) * n);
    if(!set)
    {
        fprintf(stderr, "malloc");
        return 1;
    }
   
    int i = 0;
    while(i < n)
    {
        set[i] = atoi(argv[i + 2]);
        i++;
    }
   
    int *subset = malloc(sizeof(int) * n);
    if(!subset)
    {
        fprintf(stderr, "malloc");
        free(set);
        return 1;
    }
   
    solve(set, n, target, 0, 0, subset, 0);
   
    free(set);
    free(subset);
    return 0;
}