#include <stddef.h>
#include <stdint.h>
#include <kernel/mem.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <kernel/shell.h>

#define BUFSIZE 1024

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

void shell_loop()
{
	char * line;
	char ** args;
	int status = 0;

	do {
		puts("> ");
		line = read_line();
		puts(line);
		if (line != '\n')
		{
			putc('\n');
		}

		//args = lsh_split_line(line);
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
