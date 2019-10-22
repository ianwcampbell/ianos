#include <common/stdlib.h>
#include <stdint.h>

__inline__ uint32_t div(uint32_t dividend, uint32_t divisor)
{
    uint32_t denom=divisor;
    uint32_t current = 1;
    uint32_t answer = 0;

    if (denom > dividend)
    {
        return 0;
    }
    
    if (denom == dividend)
    {
        return 1;
    }

    while (denom <= dividend)
    {
        denom <<= 1;
        current <<= 1;
    }
    
    denom >>= 1;
    current >>= 1;

    while (current!=0) 
    {
        if (dividend >= denom)
        {
            dividend -= denom;
            answer |= current;
        }
        current >>= 1;
        denom >>= 1;
    }
    return answer;
}

__inline__ divmod_t divmod(uint32_t dividend, uint32_t divisor)
{
    divmod_t res;
    res.div = div(dividend, divisor);
    res.mod = dividend - res.div*divisor;

    return res;
}
void bzero(void * dest, int bytes) {
    char * d = dest;
    while (bytes--) {
        *d++ = 0;
    }
}

char * itoa(int num, int base) {
    static char intbuf[33];
    uint32_t j = 0, isneg = 0, i;
    
    if (i == 0) {
        intbuf[0] = '0';
        intbuf[1] = '\0';
        return intbuf;
    }

    if (i < 0) {
        isneg = 1;
        i = -i;
    }

    while (i != 0) {
       intbuf[j++] = '0' + (i % 10); 
       i /= 10;
    }

    if (isneg)
        intbuf[j++] = '-';

    intbuf[j] = '\0';
    j--;
    i = 0;
    while (i < j) {
        isneg = intbuf[i];
        intbuf[i] = intbuf[j];
        intbuf[j] = isneg;
        i++;
        j--;
    }

    return intbuf;
}

