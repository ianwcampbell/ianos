#include <kernel/uart.h>
#include <common/stdio.h>
#include <common/stdlib.h>
#include <stdarg.h>

char getc(void) {
    return uart_getc();
}

void putc(char c) {
    uart_puts(&c);
    return;
}

void puts(char * str) {
    //int i;
    //for (i = 0; str[i] != '\0'; i ++)
    //{
        //putc(str[i]);
    //}
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

// BROKEN DON'T USE!
void printf(char *fmt, ...)
{
    char * traverse;

    va_list args;
    va_start(args, fmt);
    
    for(traverse = fmt; *traverse != '\0'; traverse++)
    {
        while(*traverse != '%')
        {
            putc(*traverse);
            traverse++;
        }
    
        switch (*traverse)
        {
            case 'c':
                putc(va_arg(args, int));
                break;
            case 'd':
                puts(itoa(va_arg(args, int), 10));
                break;
            case 'x':
                puts(itoa(va_arg(args, unsigned int), 16));
                break;
            case 's':
                puts(va_arg(args, char *));
                break;
            default:
                break;
        }
    }
    va_end(args);
} 
