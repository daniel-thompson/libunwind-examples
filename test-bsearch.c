#include <stdio.h>
#include <stdlib.h>

#define lengthof(x) (sizeof(x) / sizeof(x[0]))

int cmp(const void *a, const void *b)
{
	while (1)
		;
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
