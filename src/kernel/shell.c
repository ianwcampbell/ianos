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

int execute(char ** args)
{
    puts(args[0]);
    puts(args[1]);
    putc('\n');
    if(strcmp(args[0], "exit") == 0)
    {
        puts("Did exit");
        return 1;
    }
    else
    {
        puts(args[0]);
    }

    return 0;
}

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

char ** split_line(char * line)
{
    int num_tokens = get_spaces(line) + 1;
    int pos = 0;
    char ** tokens = kmalloc((num_tokens + 1) * sizeof(char*));
    char * token;

    token = strtok(line, DELIM);
    while (pos < num_tokens)
    {
        tokens[pos] = token;
        puts(token);
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

	do {
		puts("> ");
		line = read_line();
		if(line == NULL)
		{
			puts("BUFFER FAILED");
			return;
		}
		args = split_line(line);
		kfree(line);
		bzero(line, BUFSIZE);
		status = execute(args);
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
