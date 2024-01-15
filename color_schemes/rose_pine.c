#include "color_scheme.h"

// From: https://github.com/rose-pine/neovim/blob/main/lua/rose-pine/palette.lua

typedef struct {
	ANSI_Color _nc;
	ANSI_Color base;
	ANSI_Color surface;
	ANSI_Color overlay;
	ANSI_Color muted;
	ANSI_Color subtle;
	ANSI_Color text;
	ANSI_Color love;
	ANSI_Color gold;
	ANSI_Color rose;
	ANSI_Color pine;
	ANSI_Color foam;
	ANSI_Color iris;
	ANSI_Color highlight_low;
	ANSI_Color highlight_med;
	ANSI_Color highlight_high;
} Palette;

static Palette main = {
	._nc = 0x16141f,
	.base = 0x191724,
	.surface = 0x1f1d2e,
	.overlay = 0x26233a,
	.muted = 0x6e6a86,
	.subtle = 0x908caa,
	.text = 0xe0def4,
	.love = 0xeb6f92,
	.gold = 0xf6c177,
	.rose = 0xebbcba,
	.pine = 0x31748f,
	.foam = 0x9ccfd8,
	.iris = 0xc4a7e7,
	.highlight_low = 0x21202e,
	.highlight_med = 0x403d52,
	.highlight_high = 0x524f67,
};

ANSI_Color color_scheme_rose_pine(TokenType t) {
	switch(t) {
		case TOKEN_TYPE_PREPROC:
			return main.iris;
		case TOKEN_TYPE_SYS_LIB_STRING:
		case TOKEN_TYPE_STRING:
		case TOKEN_TYPE_NUMBER_LITERAL:
		case TOKEN_TYPE_CHARACTER:
			return main.gold;
		case TOKEN_TYPE_KEYWORD:
		case TOKEN_TYPE_PRIMITIVE:
		case TOKEN_TYPE_ESCAPE_SEQUENCE:
			return main.pine;
		case TOKEN_TYPE_OPERATOR:
		case TOKEN_TYPE_DELIMITER:
		case TOKEN_TYPE_PUNCTUATION:
			return main.subtle;
		case TOKEN_TYPE_TYPE_IDENTIFIER:
		case TOKEN_TYPE_FIELD_IDENTIFIER:
			return main.foam;
		case TOKEN_TYPE_IDENTIFIER:
			return main.text;
		default:
			return 0xff00ff;
	}
}
