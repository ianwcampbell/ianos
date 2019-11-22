#include "uart.h"

char getc() {
    return uart_getc();
}

void putc(char c) {
    uart_puts(&c);
    return;
}

void puts(char * str) {
    uart_puts(str);
    return;
}

void gets(char * buf, int buflen) {
    int i;
    char c[2];
    // necessary to not have padded strings print out
    c[1] = '\0';
    
    for(i = 0; i<buflen; i++)
    {
        c[0] = uart_getc();
        if(c[0] == '\n')
        {
            puts("\n");
            buf[i] = '\0';
            break;
        }
        puts(c);
        buf[i] = c[0];
    }
    return;
}

