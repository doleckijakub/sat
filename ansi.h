#ifndef ANSI_H
#define ANSI_H

#include <stdint.h>

#define ANSI_RESET         "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_UNDERLINE     "\x1b[4m"
#define ANSI_BLACK         "\x1b[30m"
#define ANSI_RED           "\x1b[31m"
#define ANSI_GREEN         "\x1b[32m"
#define ANSI_YELLOW        "\x1b[33m"
#define ANSI_BLUE          "\x1b[34m"
#define ANSI_MAGENTA       "\x1b[35m"
#define ANSI_CYAN          "\x1b[36m"
#define ANSI_WHITE         "\x1b[37m"

typedef uint32_t ANSI_Color;

#define ANSI_COLOR_ARG(color) \
	((color) >> 16 & 0xff), \
	((color) >>  8 & 0xff), \
	((color) >>  0 & 0xff)

#define ANSI_COLOR_FMT "\x1b[38;2;%d;%d;%dm"

// so that we can have code like this
// ANSI_Color color = ...;
// printf("Uncolored text" ANSI_COLOR_FMT "Colored text", ANSI_COLOR_ARG(color));

#endif
