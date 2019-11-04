#include <stddef.h>
#include <stdint.h>
#include <kernel/mem.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <kernel/shell.h>
#include <kernel/bin.h>
#include <common/string.h>

#define BUFSIZE 256
#define TOK_BUFSIZE 32
#define DELIM " \t\r\n\a"

char * read_line(void)
{
	char * buffer = kmalloc(BUFSIZE * sizeof(char));
	if(!buffer)
	{
        puts("Couldn't allocate resources to read line buffer...\n");
		return NULL;
	}
	gets(buffer, BUFSIZE);
	return buffer;
}

char ** split_line(char * line, int num_tokens)
{
    int pos = 0;
    char ** tokens = kmalloc((num_tokens + 1) * sizeof(char*));
    char * token;

    token = strtok(line, DELIM);
    while (pos < num_tokens)
    {
        tokens[pos] = token;
        token = strtok(NULL, DELIM);
        pos++;        
    }
    tokens[pos] = NULL;
    return tokens;
}

void shell_loop()
{
	char * line;
	char ** args;
	int status = 0;
    int num_tokens;

	do {
		puts("> ");
		line = read_line();
		if(line == NULL)
		{
			puts("BUFFER FAILED");
			return;
		}
        else if(strcmp(line, "\0") == 0)
        {
            kfree(line);
            bzero(line, BUFSIZE);
            continue;
        }
        num_tokens = get_spaces(line) + 1;
		args = split_line(line, num_tokens);
		status = execute(args, num_tokens);
		kfree(line);
		bzero(line, BUFSIZE);

        if(status == 1)
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
