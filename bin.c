#include "bin.h"
#include "list.h"
#include "string.h"
#include "stdio.h"
#include <stddef.h>

struct list_head binary_list;
int added_binaries = 0;

int get_binary(char * binary)
{
    struct binary * tmp;
    int internal_counter = 0;
    
    list_for_each_entry(tmp, &binary_list, list)
    {
        if(internal_counter > added_binaries - 1)
        {
            puts("Hey that is not a valid command...type 'help' for the available options...\n");
            break;
        } 
        if(strcmp(tmp->name, binary) == 0)
        {
            return tmp->callback();
        }
        internal_counter++;
    }
    return 0;
}

int execute(char ** args, int num_args)
{
    int ret = 0;
    for(int i = 0; i < num_args; i++)
    {
        ret = get_binary(args[i]); 
    }
    return ret;
}

void add_binary(char * name, function_pointer_t callback)
{
    puts("Added binary\n");
    struct binary * bin = kmalloc(sizeof(struct binary));
    bin->name = name;
    bin->callback = callback;
    list_add(&bin->list, &binary_list);
    added_binaries++;
    return;
}

int help()
{
    struct binary * tmp;
    int ret = 0;
    int internal_counter = 0;

    puts("Here is the help menu\n");
    list_for_each_entry(tmp, &binary_list, list)
    {
        if(internal_counter > added_binaries - 1)
        {
            break;
        }
        puts("\t");
        puts(tmp->name);
        puts("\n");
        internal_counter++;
    }
    return ret;
} 

int shutdown()
{
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

void setup_binaries()
{
    add_binary("help", help);
    add_binary("shutdown", shutdown);
    add_binary("mem_info", mem_info);
    add_binary("version_print", version);
    return;
} 

