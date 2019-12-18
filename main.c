#include "uart.h"
#include "mbox.h"
#include "power.h"
#include "stdio.h"
#include "shell.h"

void main()
{
    // set up serial io on GPIO pins 14 and 15
    uart_init();
    puts("Uart has been initialized...\n");
    
    // Start interactive shell
    puts("Starting up interactive shell....\n");
    start_shell();
    
    puts("Shutting down...\n");
    power_off();
}
