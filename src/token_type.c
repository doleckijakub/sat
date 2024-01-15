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
	{ "preproc_directive", TOKEN_TYPE_PREPROC },
	{ "defined", TOKEN_TYPE_PREPROC },
	{ "preproc_arg", TOKEN_TYPE_PREPROC },

	{ "system_lib_string", TOKEN_TYPE_SYS_LIB_STRING },
	
	{ "\"",             TOKEN_TYPE_STRING },
	{ "string_content", TOKEN_TYPE_STRING },
	
	{ "character", TOKEN_TYPE_CHARACTER },
	{ "'", TOKEN_TYPE_CHARACTER },
	
	{ "if", TOKEN_TYPE_KEYWORD },
	{ "else", TOKEN_TYPE_KEYWORD },
	{ "static", TOKEN_TYPE_KEYWORD },
	{ "const",  TOKEN_TYPE_KEYWORD },
	{ "return", TOKEN_TYPE_KEYWORD },
	{ "typedef", TOKEN_TYPE_KEYWORD },
	{ "struct", TOKEN_TYPE_KEYWORD },
	{ "while", TOKEN_TYPE_KEYWORD },
	{ "volatile", TOKEN_TYPE_KEYWORD },
	{ "inline", TOKEN_TYPE_KEYWORD },
	{ "sizeof", TOKEN_TYPE_KEYWORD },
	{ "long", TOKEN_TYPE_KEYWORD },
	{ "signed", TOKEN_TYPE_KEYWORD },
	{ "unsigned", TOKEN_TYPE_KEYWORD },
	{ "for", TOKEN_TYPE_KEYWORD },
	{ "break", TOKEN_TYPE_KEYWORD },
	{ "goto", TOKEN_TYPE_KEYWORD },
	{ "do", TOKEN_TYPE_KEYWORD },
	{ "continue", TOKEN_TYPE_KEYWORD },
	{ "switch", TOKEN_TYPE_KEYWORD },
	{ "case", TOKEN_TYPE_KEYWORD },
	{ "default", TOKEN_TYPE_KEYWORD },
	{ "union", TOKEN_TYPE_KEYWORD },

	{ "primitive_type", TOKEN_TYPE_PRIMITIVE },
	
	{ "comment", TOKEN_TYPE_COMMENT },

	{ "%",  TOKEN_TYPE_OPERATOR },
	{ "?",  TOKEN_TYPE_OPERATOR },
	{ "!",  TOKEN_TYPE_OPERATOR },
	{ "~",  TOKEN_TYPE_OPERATOR },
	{ "+",  TOKEN_TYPE_OPERATOR },
	{ "+=", TOKEN_TYPE_OPERATOR },
	{ "-",  TOKEN_TYPE_OPERATOR },
	{ "-=", TOKEN_TYPE_OPERATOR },
	{ "*",  TOKEN_TYPE_OPERATOR },
	{ "*=", TOKEN_TYPE_OPERATOR },
	{ "/",  TOKEN_TYPE_OPERATOR },
	{ "/=", TOKEN_TYPE_OPERATOR },
	{ ">",  TOKEN_TYPE_OPERATOR },
	{ ">=", TOKEN_TYPE_OPERATOR },
	{ "<",  TOKEN_TYPE_OPERATOR },
	{ "<=", TOKEN_TYPE_OPERATOR },
	{ "==", TOKEN_TYPE_OPERATOR },
	{ "!=", TOKEN_TYPE_OPERATOR },
	{ "=",  TOKEN_TYPE_OPERATOR },
	{ "--", TOKEN_TYPE_OPERATOR },
	{ "++", TOKEN_TYPE_OPERATOR },
	{ "^", TOKEN_TYPE_OPERATOR },
	{ "^=", TOKEN_TYPE_OPERATOR },
	{ "|", TOKEN_TYPE_OPERATOR },
	{ "||", TOKEN_TYPE_OPERATOR },
	{ "|=", TOKEN_TYPE_OPERATOR },
	{ "&", TOKEN_TYPE_OPERATOR },
	{ "&&", TOKEN_TYPE_OPERATOR },
	{ "&=", TOKEN_TYPE_OPERATOR },
	{ "<<", TOKEN_TYPE_OPERATOR },
	{ "<<=", TOKEN_TYPE_OPERATOR },
	{ ">>", TOKEN_TYPE_OPERATOR },
	{ ">>=", TOKEN_TYPE_OPERATOR },

	{ "identifier", TOKEN_TYPE_IDENTIFIER },
	{ "type_identifier", TOKEN_TYPE_TYPE_IDENTIFIER },
	{ "field_identifier", TOKEN_TYPE_FIELD_IDENTIFIER },
	{ "...", TOKEN_TYPE_FIELD_IDENTIFIER },
	{ "statement_identifier", TOKEN_TYPE_STATEMENT_IDENTIFIER },
	{ ":", TOKEN_TYPE_STATEMENT_IDENTIFIER },

	{ ";", TOKEN_TYPE_DELIMITER },
	{ ".", TOKEN_TYPE_DELIMITER },
	{ "->", TOKEN_TYPE_DELIMITER },
	{ "\n", TOKEN_TYPE_DELIMITER },

	{ "(", TOKEN_TYPE_PUNCTUATION },
	{ ")", TOKEN_TYPE_PUNCTUATION },
	{ "{", TOKEN_TYPE_PUNCTUATION },
	{ "}", TOKEN_TYPE_PUNCTUATION },
	{ "[", TOKEN_TYPE_PUNCTUATION },
	{ "]", TOKEN_TYPE_PUNCTUATION },
	{ ",", TOKEN_TYPE_PUNCTUATION },

	{ "number_literal", TOKEN_TYPE_NUMBER_LITERAL },
	{ "NULL", TOKEN_TYPE_NUMBER_LITERAL },

	{ "escape_sequence", TOKEN_TYPE_ESCAPE_SEQUENCE },

	{ "false", TOKEN_TYPE_BOOLEAN },
	{ "FALSE", TOKEN_TYPE_BOOLEAN },
	{ "true", TOKEN_TYPE_BOOLEAN },
	{ "TRUE", TOKEN_TYPE_BOOLEAN },
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
