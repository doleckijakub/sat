#ifndef COLOR_SCHEMES_H
#define COLOR_SCHEMES_H

#include "color_scheme.h"

// include color scheme names here

#define COLOR_SCHEMES(X) \
	X(rose_pine)

//

#define COLOR_SCHEME_NAME(color_scheme) #color_scheme
#define COLOR_SCHEME_FUNC(color_scheme) color_scheme_##color_scheme

#define X(color_scheme) ANSI_Color COLOR_SCHEME_FUNC(color_scheme)(TokenType);
	COLOR_SCHEMES(X)
#undef X

ColorScheme get_color_scheme(void);
void set_color_scheme(ColorScheme);

#endif
