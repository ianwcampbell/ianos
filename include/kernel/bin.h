#ifndef _BIN_H_
#define _BIN_H_

#include <kernel/bin.h>

typedef void (*function_pointer_t)();

typedef struct binary {
    char * name;
	function_pointer_t callback;
	DEFINE_LINK(binary);
} binary_t;

int execute(char ** args, int num_args);
void setup_binaries();

#endif
