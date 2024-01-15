#ifndef FORMATTER_H
#define FORMATTER_H

#include <stddef.h>

typedef enum {
	LANG_NONE = 0,
	LANG_C
} Lang;

void print_formatted_file(Lang language, const char *content, size_t len);

#endif
