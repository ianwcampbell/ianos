#include "bin.h"
#include "string.h"
#include "stdio.h"
#include "serial_num.h"
#include "delay.h"
#include "power.h"
#include <stddef.h>

#define BIN         7

int default_wait = 1000000;

static char * binary_locals[BIN] = {"shutdown\0", "help\0", "version_print\0", "mem_info\0", "get_serial\0", "wait\0", "reboot\0"};

int help()
{
    int ret = 0;
    puts("Here is the help menu\n");
    for(int i = 0; i < BIN; i++)
    {
        puts("\t");
        puts(binary_locals[i]);
        puts("\n");
    } 
    return ret;
} 

int shutdown()
{
    puts("Here is shutdown!!\n");
    int ret = -1;
    return ret;
}
    
int mem_info()
{
    int ret = 0;
    puts("Memory information binary\n");
    return ret;
}

int version()
{
    int ret = 0;
    puts(
        "  _____          _   _  ____   _____  \n"
        " |_   _|   /\\   | \\ | |/ __ \\ / ____| \n"
        "   | |    /  \\  |  \\| | |  | | (___   \n" 
        "   | |   / /\\ \\ | . ` | |  | |\\___ \\  \n" 
        "  _| |_ / ____ \\| |\\  | |__| |____) | \n"
        " |_____/_/    \\_\\_| \\_|\\____/|_____/  \n\n");
    puts("ianos 0.2\n");
    return ret;
}

int get_binary(char * binary)
{
    if(strcmp(binary, "mem_info") == 0)
    {
        return mem_info();
    }
    else if(strcmp(binary, "version_print") == 0)
    {
        return version();
    }
    else if(strcmp(binary, "help") == 0)
    {
        return help();
    }
    else if(strcmp(binary, "shutdown") == 0)
    {
        return shutdown();
    }
    else if(strcmp(binary, "get_serial") == 0)
    {
        return get_serial();
    }
    else if(strcmp(binary, "wait") == 0)
    {
        wait_msec(default_wait);
    }
    else if(strcmp(binary, "reboot") == 0)
    {
        puts("Gotcha\n");
        reset();    
    }
    else
    {
        puts("Hey that binary was not found...try 'help'!\n");
    }
    return 0;
}

int execute(int num_args, char args[num_args][32])
{
    int ret = 0;
    for(int i = 0; i < num_args; i++)
    {
        puts("Looping...here is the binary...");
        puts(args[i]);
        puts("\n");
        ret = get_binary(args[i]); 
    }
    return ret;
}

