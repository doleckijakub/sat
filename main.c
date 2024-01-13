#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static const char *program;

const char *next_arg(int *argc, const char ***argv) {
	assert(*argc > 0);
	const char *arg = **argv;
	--*argc;
	++*argv;
	return arg;
}

int read_file(const char *path, char **content, size_t *len) {
	errno = 0;

	FILE *fp = fopen(path, "rb");
	if(fp == NULL) goto error;

	if(fseek(fp, 0, SEEK_END)) goto error;

	*len = ftell(fp);
	if(*len == -1) goto error;

	if(fseek(fp, 0, SEEK_SET)) goto error;

	*content = (char*) malloc(*len);
	if(*content == NULL) goto error;

	if(fread(*content, sizeof(char), *len, fp) != *len) goto error;
	
	fclose(fp);

	return 0;
error:
	if(fp) fclose(fp);
	return 1;
}

void print_file(const char *path) {
	char *content;
	size_t len;

	if(read_file(path, &content, &len)) {
		fprintf(stderr, "%s: %s: %s\n", program, path, strerror(errno));
	} else {
		printf("%*s\n", (int) len, content);
	}
}

int main(int argc, const char **argv) {
	program = next_arg(&argc, &argv);
	
	while(argc) {
		print_file(next_arg(&argc, &argv));
	}
}
