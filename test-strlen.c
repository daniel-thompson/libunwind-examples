#include <assert.h>
#include <stdlib.h>
#include <string.h>

char buf[8*1024*1024];

// strlen() can be implemented entirely inline on some architectures...
// calling it via a function pointer defeats this.
typedef size_t (*strlen_t)(const char *);
strlen_t getlen = strlen;

int main(int argc, char **argv)
{
	memset(buf, '+', sizeof(buf)-1);

	while (1) {
		size_t len = getlen(buf);
		assert(len == sizeof(buf) - 1);
	}

	// not reached
	return 1;
}
