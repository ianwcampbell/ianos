#include <stddef.h>
#include <stdint.h>
#include <kernel/mem.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <kernel/shell.h>
#include <common/string.h>

#define BUFSIZE 256
#define TOK_BUFSIZE 32
#define DELIM " \t\r\n\a"

char * read_line(void)
{
	char * buffer = kmalloc(BUFSIZE * sizeof(char));
    puts("Malloced read line buffer\n");
	if(!buffer)
	{
        puts("Couldn't allocate resources to read line buffer...\n");
		return NULL;
	}
	gets(buffer, BUFSIZE);
	return buffer;
}

char ** split_line(char * line)
{
    int pos = 0;
    int bufsize = TOK_BUFSIZE;
    char ** tokens = kmalloc(bufsize * sizeof(char*));
    char * token;

    if(!tokens)
    {
        puts("Couldn't allocate resources for tokens...\n");
    }
    puts("Malloced tokens...\n");

    token = strtok(line, DELIM);
    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;

        if (pos >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = krealloc(tokens, bufsize * sizeof(char*));
            puts("Realloced tokens\n");
            if (!tokens)
            {
                puts("REALLOC FAILED\n");
                return NULL;
            }  
        }
        token = strtok(NULL, DELIM);
    }
    tokens[pos] = NULL;
    puts("returning tokens\n");
    return tokens;
}

void shell_loop()
{
	char * line;
	char ** args;
	int status = 0;

	do {
		puts("> ");
		line = read_line();
		if(line == NULL)
		{
			puts("BUFFER FAILED");
			return;
		}

		puts(line);
		putc('\n');
		args = split_line(line);
		//status = lsh_execute(args);
		kfree(line);
		bzero(line, BUFSIZE);
		kfree(args);
	} while (1);
}

void start_shell()
{
	shell_loop();
	return;
}
