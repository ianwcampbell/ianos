#include "uart.h"
#include "mbox.h"
#include "stdio.h"

int get_serial()
{
    // get the board's unique serial number with a mailbox call
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = MBOX_TAG_GETSERIAL;   // get serial number command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if (mbox_call(MBOX_CH_PROP))
    {
        puts("My serial number is: ");
        uart_hex(mbox[6]);
        uart_hex(mbox[5]);
        puts("\n");
    } 
    else 
    {
        puts("Unable to query serial!\n");
        return -1;
    }

    return 0;
}
