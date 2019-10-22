#ifndef STDLIB_H
#define STDLIB_H
#include <stdint.h>

typedef struct divmod_result {
    uint32_t div;
    uint32_t mod;
} divmod_t;

divmod_t divmod(uint32_t dividend, uint32_t divisor);
uint32_t div(uint32_t dividend, uint32_t divisor);

void bzero(void * dest, int bytes);

char * itoa(int num, int i);

#endif
