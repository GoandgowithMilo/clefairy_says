#include <stdio.h>

/* returns true if the strings are the same and false otherwise*/ 
int str_compare(int len, char s1[], char s2[])
{

    for(int i = 0; i < len; i++)
    {
        if(s1[i] == s2[i])
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}
