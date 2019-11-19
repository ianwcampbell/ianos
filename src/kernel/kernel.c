#include <stddef.h>
#include <stdint.h>
#include "kernel/uart.h"
#include "kernel/mbox.h"
#include "kernel/mem.h"
#include "kernel/atag.h"
#include "common/stdio.h"
#include "common/stdlib.h"
#include "kernel/shell.h"
#include "kernel/bin.h"

void kernel_main(uint32_t r0, uint32_t r1, uint64_t atags)
{
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();

    mbox[0] = 8*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_GETSERIAL;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = 0;
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

    if(mbox_call(MBOX_CH_PROP))
    {
        uart_puts("My serial number is: ");
        uart_hex(mbox[6]);
        uart_hex(mbox[5]);
        uart_puts("\n");
    }
    else
    {
        uart_puts("Unable to query...\n");
    }

    puts("Initializing Serial I/O Module\n");
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
