#include <stdlib.h>
#include <stdio.h>

int len(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

void swap(char *a, char *b)
{
    char c = *a;
    *a = *b;
    *b = c;
}

void solve(char *s, int n, int *used, char *perm, int index)
{
    if (index == n)
    {
        perm[index] = 0;
        puts(perm);
        return ;
    }

    int i = 0;
    while (i < n)
    {
        if (!used[i])
        {
            used[i] = 1;
            perm[index] = s[i];
            solve(s, n, used, perm, index + 1);
            used[i] = 0;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);

    char *s = argv[1];
    int n = len(s);

    int i = 0;
    while (i < n)
    {
        int j = i + 1;
        while (j < n)
        {
            if (s[i] > s[j])
                swap(&s[i], &s[j]);
            j++;
        }
        i++;
    }

    int *used = calloc(n, sizeof(int));
    char *perm = malloc(n + 1);

    if (!used || !perm)
        return (1);

    solve(s, n, used, perm, 0);

    free(used);
    free(perm);
    return (0);
}