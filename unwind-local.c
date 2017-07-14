#include <stdio.h>
#include <stdlib.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include "die.h"

#define lengthof(x) (sizeof(x) / sizeof(x[0]))

void backtrace()
{
	unw_cursor_t cursor;
	unw_context_t context;

	// grab the machine context and initialize the cursor
	if (unw_getcontext(&context) < 0)
		die("ERROR: cannot get local machine state\n");
	if (unw_init_local(&cursor, &context) < 0)
		die("ERROR: cannot initialize cursor for local unwinding\n");


	// currently the IP is within backtrace() itself so this loop
	// deliberately skips the first frame.
	while (unw_step(&cursor) > 0) {
		unw_word_t offset, pc;
		char sym[4096];
		if (unw_get_reg(&cursor, UNW_REG_IP, &pc))
			die("ERROR: cannot read program counter\n");

		printf("0x%lx: ", pc);

		if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0)
			printf("(%s+0x%lx)\n", sym, offset);
		else
			printf("-- no symbol name found\n");
	}
}

int cmp(const void *a, const void *b)
{
	backtrace();
	exit(0);
}

int main(int argc, char **argv)
{
	int data[] = {1, 2, 3, 4};
	int needle = 4;

	// ensure we backtrace through dynamically linked symbols too
	bsearch(&needle, data, lengthof(data), sizeof(data[0]), cmp);

	// not reached
	return 1;
}
