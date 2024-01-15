#include "token_type.h"

#include "ansi.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	const char *key;
	TokenType value;
} TokenMapEntry;

static TokenMapEntry token_map[] = {
	{ "#if",       TOKEN_TYPE_PREPROC },
	{ "#elif",     TOKEN_TYPE_PREPROC },
	{ "#else",     TOKEN_TYPE_PREPROC },
	{ "#endif",    TOKEN_TYPE_PREPROC },
	{ "#ifdef",    TOKEN_TYPE_PREPROC },
	{ "#define",   TOKEN_TYPE_PREPROC },
	{ "#ifndef",   TOKEN_TYPE_PREPROC },
	{ "#include",  TOKEN_TYPE_PREPROC },
	{ "#elifdef",  TOKEN_TYPE_PREPROC },
	{ "#elifndef", TOKEN_TYPE_PREPROC },
};

TokenType token_type_from_str(const char *str) {
	for(size_t i = 0; i < sizeof(token_map) / sizeof(*token_map); ++i) {
		if(strcmp(token_map[i].key, str) == 0) {
			return token_map[i].value;
		}
	}

	printf(ANSI_RESET "\nUnhandled token type: '%s'\n", str);
	exit(1);
}
