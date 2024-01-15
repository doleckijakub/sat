#ifndef READ_FILE_H
#define READ_FILE_H

#include <errno.h>
#include <stddef.h>

int read_file(const char *path, char **content, size_t *len);

#endif
