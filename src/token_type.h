#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

typedef enum {
	TOKEN_TYPE_UNKNOWN = 0,
	TOKEN_TYPE_PREPROC,
} TokenType;

TokenType token_type_from_str(const char *str);

#endif
