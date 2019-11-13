#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/mem.h>
#include <kernel/atag.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <kernel/shell.h>
#include <kernel/bin.h>

void kernel_main(uint32_t r0, uint32_t r1, uint64_t atags)
{
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    puts("Initializing Serial I/O Module\n");
    uart_init();
    puts("Complete...\n");
    puts("Initializing Memory Module\n");
    mem_init((atag_t *)atags);
    puts("Complete...\n");
    puts("Initializing Binary Module\n");
    setup_binaries();
    puts("Complete...\n");

    puts("Welcome to IanOS!!\n");
    puts("Starting Kernel level shell...\n");
    start_shell();
    return;
}
