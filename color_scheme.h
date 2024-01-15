#ifndef COLOR_SCHEME_H
#define COLOR_SCHEME_H

#include "ansi.h"
#include "token_type.h"

typedef ANSI_Color(*ColorScheme)(TokenType);

#endif
