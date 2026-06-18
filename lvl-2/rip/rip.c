#include <unistd.h>
#include <stdio.h>


void solve(char *s, int index, int balance, int rem_open, int rem_close)
{
    if (!s[index])
    {
        if (balance == 0 && rem_open == 0 && rem_close == 0)
            puts(s);
        return;
    }

    if (s[index] == '(')
    {
        if (rem_open > 0)
        {
            s[index] = ' ';
            solve(s, index + 1, balance, rem_open - 1, rem_close);
            s[index] = '(';
        }

        solve(s, index + 1, balance + 1, rem_open, rem_close);
    }
    else
    {
        if (rem_close > 0)
        {
            s[index] = ' ';
            solve(s, index + 1, balance, rem_open, rem_close - 1);
            s[index] = ')';
        }

        if (balance > 0)
            solve(s, index + 1, balance - 1, rem_open, rem_close);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);

    char *s = argv[1];

    int rem_open = 0;
    int rem_close = 0;

    int i = 0;
    while (s[i])
    {
        if (s[i] == '(')
            rem_open++;
        else if (s[i] == ')')
        {
            if (rem_open > 0)
                rem_open--;
            else
                rem_close++;
        }
        i++;
    }

    solve(s, 0, 0, rem_open, rem_close);
    return (0);
}