#include "get_next_line.h"

int slen(char *s)
{
    if(!s) return 0;
    int i = 0;
    while(s[i]) i++;
    return i;
}

char *sjoin(char *s1, char *s2)
{
    char *ret;
    int i = 0, j = 0;
    if(!s1)
    {
        s1 = malloc(1);
        if(!s1) return NULL;
        s1[0] = 0;
    }
    ret = malloc(slen(s1) + slen(s2) + 1);
    if(!ret)
    {
        free(s1);
        return NULL;
    }
    while(s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    while(s2[j]) ret[i++] = s2[j++];
    ret[i] = 0;
    free(s1);
    return ret;
   
}

char *schr(char *s, int c)
{
    if(!s) return NULL;
    int i = 0;
    while(s[i])
    {
        if(s[i] == (char )c) return (char *)&s[i];
        i++;
    }
   
    if(s[i] == (char )c) return (char *)&s[i];
    return NULL;
}

char *extract(char *stash)
{
    if(!stash || !stash[0]) return NULL;
    int i = 0;
    while(stash[i] && stash[i] != '\n') i++;
    char *new = malloc(i + (stash[i] == '\n') + 1);
    if(!new)
    {
        free(stash);
        return NULL;
    }
    i = 0;
    while(stash[i] && stash[i] != '\n')
    {
        new[i] = stash[i];
        i++;
    }
    if(stash[i] == '\n') new[i++] = '\n';
   
    new[i] = 0;
   
    return new;
}

char *clear(char *stash)
{
    if(!stash) return NULL;
    int i = 0;
    char *new;
    while(stash[i] && stash[i] != '\n') i++;
    if(!stash[i])
    {
        free(stash);
        return NULL;
    }
    i++;
    new = malloc(slen(stash) - i + 1);
    if(!new)
    {
        free(stash);
        return NULL;
    }
    int j = 0;
    while(stash[i])
    {
        new[j++] = stash[i];
        i++;
    }
    new[j] = 0;
    free(stash);
    return new;
}

char *get_next_line(int fd)
{
    char buff[BUFFER_SIZE + 1];
    char *new;
    static char *stash;
    int r = 1;
   
    if(fd < 0 || BUFFER_SIZE < 1) return NULL;
   
    while(!schr(stash, '\n') && r > 0)
    {
        r = read(fd, buff, BUFFER_SIZE);
        if(r < 0)
        {
            free(stash);
            stash = NULL;
            return NULL;
        }
        buff[r] = 0;
        stash = sjoin(stash, buff);
    }
    if(!stash) return NULL;
   
    new = extract(stash);
    stash = clear(stash);
   
    return new;
}


#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *s;
    while((s = get_next_line(fd)) != NULL)
    {
        printf("%s", s);
        free (s);
    }
    close(fd);
    return 0;
}