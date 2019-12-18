#include "stdio.h"
#include <stddef.h>

int get_spaces(char * str)
{
    int i = 0;
    char *p = str;
    while( *p != '\0' )
    {
        if( *(p-1) == ' ' && *(p+1) != '\0')
        {
            i++;
        }
        p++;
    }
    return i;
} 

int strcmp(const char * src1, const char * src2)
{
    while((*src1 != '\0') || (*src2 != '\0'))
    {
        if(*src1 > *src2)
        {
            return 1;
        }
        if(*src1 < *src2)
        {
            return 1;
        }
        
        src1++;
        src2++;
    }
    return 0;
}

char * strtok(char * str, const char* delim)
{
    static char* buffer;
    if ( str != NULL)
    {
        buffer = str;
    }

    if (buffer[0] == '\0')
    {
        return NULL;
    }

    char * ret = buffer, *b;
    const char *d;

    for(b = buffer; *b != '\0'; b++)
    {
        for(d = delim; *d != '\0'; d++)
        {
            if(*b == *d)
            {
                *b = '\0';
                buffer = b+1;
        
                if(b == ret)
                {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }

    return ret;
}
