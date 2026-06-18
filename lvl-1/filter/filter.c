#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

char *append(char *stash, size_t *len, char *buff, int r)
{
    char *new = realloc(stash, *len + r);
    if(!new) return NULL;
    stash = new;
    memmove(stash + *len, buff, r);
    *len += r;
    return stash;
}

int match(char *stash, size_t len, size_t pos, char *pattern, size_t pat_len)
{
    size_t i = 0;
    if(pos + pat_len > len) return 0;
    while(i < pat_len)
    {
        if(stash[pos + i] != pattern[i]) return 0;
        i++;
    }
    return 1;
}

int process(char **stash, size_t *len, char *pattern, size_t pat_len)
{
    size_t i = 0, j, remain;
   
    while(i+pat_len <= *len)
    {
        if(match(*stash, *len, i, pattern, pat_len))
        {
            if(write(1, *stash, i) < 0) return 1;
            j = 0;
            while(j < pat_len)
            {
                if(write(1, "*", 1) < 0) return 1;
                j++;
            }
           
            remain = *len - (i + pat_len);
            memmove(*stash, *stash + i + pat_len, remain);
            *len = remain;
            i = 0;
           
        }
        else
            i++;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 2 || !argv[1][0]) return 1;
   
    char buff[BUFFER_SIZE + 1];
    char *stash = NULL;
    size_t plen = strlen(argv[1]);
    int r;
    size_t len = 0;

    while((r = read(0, buff, BUFFER_SIZE)) > 0)
    {
        stash = append(stash, &len, buff, r);
        if(!stash)
        {
            perror("Error");
            return 1;
        }
        if(process(&stash, &len, argv[1], plen))
        {
            free(stash);
            perror("Error");
            return 1;
        }
    }
   
    if(r < 0)
    {
        free(stash);
        perror("Error");
        return 1;
    }
   
    if(len > 0) write(1, stash, len);

    free(stash);
    return 0;
}