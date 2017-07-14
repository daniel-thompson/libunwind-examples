#include <sys/ptrace.h>
#include <stdio.h>
#include <stdlib.h>

#include <libunwind-ptrace.h>

#include "die.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		die("USAGE: unwind-pid <pid>\n");

	unw_addr_space_t as = unw_create_addr_space(&_UPT_accessors, 0);

	pid_t pid = atoi(argv[1]);
	if (ptrace(PTRACE_ATTACH, pid, 0, 0) != 0)
		die("ERROR: cannot attach to %d\n", pid);

	void *context = _UPT_create(pid);
	unw_cursor_t cursor;
	if (unw_init_remote(&cursor, as, context) != 0)
		die("ERROR: cannot initialize cursor for remote unwinding\n");

	do {
		unw_word_t offset, pc;
		char sym[4096];
		if (unw_get_reg(&cursor, UNW_REG_IP, &pc))
			die("ERROR: cannot read program counter\n");

		printf("0x%lx: ", pc);

		if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0)
			printf("(%s+0x%lx)\n", sym, offset);
		else
			printf("-- no symbol name found\n");
	} while (unw_step(&cursor) > 0);

	_UPT_destroy(context);
	(void) ptrace(PTRACE_DETACH, pid, 0, 0);

	return 0;
}
