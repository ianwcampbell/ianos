#ifndef _BIN_H_
#define _BIN_H_

typedef int (*function_pointer_t)();

struct binary {
    char * name;
	function_pointer_t callback;
};

int execute(int num_args, char args[num_args][32]);
#endif
