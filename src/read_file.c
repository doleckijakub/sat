#include "read_file.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

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
