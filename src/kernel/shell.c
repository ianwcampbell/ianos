#include <stddef.h>
#include <stdint.h>
#include <kernel/mem.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <kernel/shell.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 64
#define DELIM " \t\r\n\a"

char * read_line(void)
{
	char * buffer = kmalloc(BUFSIZE * sizeof(char));
	if(!buffer)
	{
		puts("Couldn't allocate buffer\n");
		return NULL;
	}
	gets(buffer, BUFSIZE);
	return buffer;
}

char ** split_line(char * line)
{
    int pos = 0;
    int bufsize = TOK_BUFSIZE;
    char ** tokens = kmalloc(bufsize * sizeof(char));
    char * token;

    if(tokens == NULL)
    {
        puts("COULD NOT MALLOC");
        return NULL;
    }

    //IMPLEMENT STRTOK TODO
    token = strtok(line, DELIM);
    while (token != NULL)
    {
        tokens[pos] = token;
        pos ++;

        if (pos >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = krealloc(tokens, bufsize * sizeof(char*));
            if (tokens == NULL)
            {
                puts("REALLOC FAILED");
                return NULL;
            }  
        }

        token = strtok(NULL, DELIM);
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

		puts(line);
		putc('\n');
		//args = split_line(line);
		//status = lsh_execute(args);
		kfree(line);
		bzero(line, BUFSIZE);
		//kfree(args);
	} while (1);
}

void start_shell()
{
	shell_loop();
	return;
}
