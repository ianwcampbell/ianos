#ifndef _BIN_H_
#define _BIN_H_

//#include "list.h"

typedef int (*function_pointer_t)();

struct binary {
    char * name;
	function_pointer_t callback;
    //struct list_head list;
};

int execute(int num_args, char args[num_args][32]);
#endif
