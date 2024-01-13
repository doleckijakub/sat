#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "formatter.h"

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

void print_file(Lang language, const char *path) {
	char *content;
	size_t len;

	if(read_file(path, &content, &len)) {
		fprintf(stderr, "%s: %s: %s\n", program, path, strerror(errno));
	} else {
		print_formatted_file(language, content, len);
	}

	free(content);
}

int streq(const char *a, const char *b) {
	return strcmp(a, b) == 0;
}

int main(int argc, const char **argv) {
	program = next_arg(&argc, &argv);

	Lang language = LANG_NONE;
	
	while(argc) {
		const char *file = next_arg(&argc, &argv);
		const char *ext = strrchr(file, '.');

		if(ext) {
			if(streq(ext, ".c")) language = LANG_C;
		}

		print_file(language, file);
		if(argc) printf("\n");
	}
}
