#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const char *program;

const char *next_arg(int *argc, const char ***argv) {
	assert(*argc > 0);
	const char *arg = **argv;
	--*argc;
	++*argv;
	return arg;
}

int main(int argc, const char **argv) {
	program = next_arg(&argc, &argv);

	printf("%s\n", program);
}
