#include "formatter.h"

#include <assert.h>
#include <stdio.h>

void print_formatted_file(Lang language, const char *content, size_t len) {
	switch(language) {
		case LANG_NONE: {
			printf("%.*s", (int) len, content);
		} break;
		case LANG_C: {
			assert(0 && "Unimplemented");
		} break;
		default: {
			assert(0 && "Unreachable");
		}
	}
}
