#include "formatter.h"

#include "token_type.h"
#include "color_schemes.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <tree_sitter/api.h>

TSLanguage *tree_sitter_c();

static void print_tree(TSNode node, const char *content) {
	ColorScheme color_scheme = get_color_scheme();
	static uint32_t prev_token_end = 0;

	uint32_t child_count = ts_node_child_count(node);
	
	if(child_count == 0) {
		uint32_t token_start = ts_node_start_byte(node);
		uint32_t token_end   = ts_node_end_byte(node);

		for(uint32_t i = prev_token_end; i < token_start; ++i) {
			putc(content[i], stdout);
		}

		prev_token_end = token_end;

		TokenType token_type = token_type_from_str(ts_node_type(node));
		ANSI_Color color = color_scheme(token_type);

		printf(ANSI_COLOR_FMT, ANSI_COLOR_ARG(color));

		for(uint32_t i = token_start; i < token_end; ++i) {
			putc(content[i], stdout);
		}
	}

	for(uint32_t i = 0; i < child_count; ++i) {
		print_tree(ts_node_child(node, i), content);
	}
}

void print_formatted_file(Lang language, const char *content, size_t len) {
	TSParser *parser = ts_parser_new();

	switch(language) {
		case LANG_NONE: {
			printf("%.*s", (int) len, content);
			return;
		} break;
		case LANG_C: {
			ts_parser_set_language(parser, tree_sitter_c());
		} break;
		default: {
			assert(0 && "Unreachable");
		}
	}

	TSTree *tree = ts_parser_parse_string(parser, NULL, content, len);

	print_tree(ts_tree_root_node(tree), content);

	ts_tree_delete(tree);
	ts_parser_delete(parser);
}
