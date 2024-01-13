#include "formatter.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <tree_sitter/api.h>

TSLanguage *tree_sitter_c();

#include "rose-pine.h"

static const char *token_type_to_color(const char *token_type) {
	static const char *token_map[][2] = {
		{ "#include", COLOR_PREPROC }, 
		{ "#ifndef", COLOR_PREPROC }, 
		{ "#define", COLOR_PREPROC }, 
		{ "!=", COLOR_NOT_EQUAL }, 
		{ "\"", COLOR_DOUBLE_QUOTE }, 
		{ "&", COLOR_AMPERSAND }, 
		{ "'", COLOR_SINGLE_QUOTE }, 
		{ "(", COLOR_LEFT_PAREN }, 
		{ ")", COLOR_RIGHT_PAREN }, 
		{ "*", COLOR_ASTERISK }, 
		{ "++", COLOR_INCREMENT }, 
		{ ",", COLOR_COMMA }, 
		{ "--", COLOR_DECREMENT }, 
		{ ":", COLOR_COLON }, 
		{ ";", COLOR_SEMICOLON }, 
		{ "=", COLOR_EQUAL }, 
		{ "==", COLOR_EQUAL_EQUAL }, 
		{ ">", COLOR_GREATER }, 
		{ "{", COLOR_LEFT_BRACE }, 
		{ "}", COLOR_RIGHT_BRACE }, 
		{ "character", COLOR_CHARACTER }, 
		{ "const", COLOR_CONST }, 
		{ "else", COLOR_ELSE }, 
		{ "escape_sequence", COLOR_ESCAPE_SEQ }, 
		{ "goto", COLOR_GOTO }, 
		{ "identifier", COLOR_IDENTIFIER }, 
		{ "if", COLOR_IF }, 
		{ "NULL", COLOR_NULL }, 
		{ "number_literal", COLOR_NUMBER }, 
		{ "primitive_type", COLOR_PRIMITIVE }, 
		{ "return", COLOR_RETURN }, 
		{ "sizeof", COLOR_SIZEOF }, 
		{ "statement_identifier", COLOR_STATEMENT }, 
		{ "static", COLOR_STATIC }, 
		{ "string_content", COLOR_STRING }, 
		{ "system_lib_string", COLOR_SYS_STRING }, 
		{ "type_identifier", COLOR_TYPE }, 
		{ "while", COLOR_WHILE } 
	};
	
	for(size_t i = 0; i < sizeof(token_map) / sizeof(*token_map); ++i) {
		if(strcmp(token_map[i][0], token_type) == 0) {
			return token_map[i][1];
		}
	}

	printf("Unhandled token type: '%s'\n", token_type);
	assert(0);
}

static void print_tree(TSNode node, const char *content) {
	static uint32_t prev_token_end = 0;

	uint32_t child_count = ts_node_child_count(node);
	
	if(child_count == 0) {
		uint32_t token_start = ts_node_start_byte(node);
		uint32_t token_end   = ts_node_end_byte(node);

		for(uint32_t i = prev_token_end; i < token_start; ++i) {
			putc(content[i], stdout);
		}

		prev_token_end = token_end;

		printf("%s", token_type_to_color(ts_node_type(node)));

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
