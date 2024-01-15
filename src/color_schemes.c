#include "color_schemes.h"

static ColorScheme color_scheme = { 0 };

ColorScheme get_color_scheme(void) {
	return color_scheme;
}

void set_color_scheme(ColorScheme c) {
	color_scheme = c;
}
