#include <kernel/bin.h>
#include <kernel/mem.h>
#include <kernel/list.h>
#include <common/string.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <stddef.h>
#include <stdint.h>

DEFINE_LIST(binary);
IMPLEMENT_LIST(binary);

binary_list_t binaries;


void get_binary(char * binary)
{
    uint32_t list_size;
    list_size = size_binary_list(&binaries);
    binary_t * bin;

    for(uint32_t i = 0; i < list_size; i++)
    {
        if(i == 0)
        {
            bin = peek_binary_list(&binaries);            
            if(strcmp(binary, bin->name) == 0)
            {
                bin->callback();
                break;
            }
        }
        else
        {
            binary_t * tmp;
            tmp = next_binary_list(bin);
            if(strcmp(binary, tmp->name) == 0)
            {
                bin->callback();
                break;
            }
            bin = tmp;
        }
    }
    return;
}

int execute(char ** args, int num_args)
{
    for(int i = 0; i < num_args; i++)
    {
        get_binary(args[i]); 
    }
    return 0;
}

void add_binary(char * name, function_pointer_t callback)
{
    binary_t bin;
    bin.name = name;
    bin.callback = callback;
    append_binary_list(&binaries, &bin);
    return;
}

void help()
{
    puts("Here is the help menu\n");
    return;
} 

void setup_binaries()
{
    INITIALIZE_LIST(binaries); 
    add_binary("help", help);
    return;
} 

