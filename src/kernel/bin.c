#include <kernel/bin.h>
#include <kernel/mem.h>
#include <common/string.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <stddef.h>
#include <stdint.h>

int execute(char ** args, int num_args)
{
    for(int i = 0; i < num_args; i++)
    {
        puts(args[i]);
        putc('\n');
    }
    return 0;
}
