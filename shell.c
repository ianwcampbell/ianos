#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include "bin.h"
#include "string.h"
#include "power.h"

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

void place_token(char buf[TOK_BUFSIZE], char * token)
{
    int i = 0;
    while(token[i] != '\0')
    {
        buf[i] = token[i];
        i++;
    }
    buf[i] = '\0';
}

void split_line(int num_tokens, char tokens[num_tokens][TOK_BUFSIZE])
{
    int pos = 0;
    char * token;

    token = strtok(buffer, DELIM);
    while (pos < num_tokens)
    {
        place_token(tokens[pos], token);
        token = strtok(NULL, DELIM);
        pos++;        
    }
    place_token(tokens[pos], "\0");
    return;
}

void shell_loop()
{
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
		split_line(num_tokens, args);
        puts(args[0]);
        puts("\n");
		status = execute(num_tokens, args);
        zero_buf();

        if(status == -1)
        {
            puts("Recieved shutdown signal...\n");
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
