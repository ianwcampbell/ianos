#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
//#include "bin.h"
#include "string.h"

#define BUFSIZE 100
#define TOK_BUFSIZE 32
#define DELIM " \t\r\n\a"

char buffer[BUFSIZE];

void zero_buf()
{
    for(int i = 0; i < BUFSIZE; i++)
    {
        buffer[i] = '\0';
    }
    return;
}

void split_line(char ** tokens, int num_tokens)
{
    int pos = 0;
    char * token;

    token = strtok(buffer, DELIM);
    while (pos < num_tokens)
    {
        tokens[pos] = token;
        token = strtok(NULL, DELIM);
        pos++;        
    }
    tokens[pos] = NULL;
    return;
}

void shell_loop()
{
	//char ** args;
	int status = 0;
    int num_tokens;

	do {
		puts("> ");
		gets(buffer, BUFSIZE);
        if(strcmp(buffer, "\0") == 0)
        {
            zero_buf();
            continue;
        }
        num_tokens = get_spaces(buffer) + 1;
        char args[num_tokens][TOK_BUFSIZE];
		split_line(args, num_tokens);
		//status = execute(args, num_tokens);
        zero_buf();

        if(status == -1)
        {
            puts("Shutting down...");
            break;
        }
	} while (1);

    return;
}

void start_shell()
{
	shell_loop();
	return;
}
