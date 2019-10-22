#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
