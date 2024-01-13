#include "formatter.h"

#include <assert.h>
#include <stdio.h>

#include <tree_sitter/api.h>

TSLanguage *tree_sitter_c();

static void dump_node(TSNode node, int depth) {
	printf("%*s%s\n", 2 * depth, " ", ts_node_type(node));

	uint32_t child_count = ts_node_child_count(node);
	for(uint32_t i = 0; i < child_count; ++i) {
		dump_node(ts_node_child(node, i), depth + 1);
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

	dump_node(ts_tree_root_node(tree), 0);

	ts_tree_delete(tree);
	ts_parser_delete(parser);
}
