.PHONY: all
all: test

CC = cc

C_FLAGS += -I tree-sitter/lib/src
C_FLAGS += -I tree-sitter/lib/include
C_FLAGS += -I .

PARSERS += parsers/tree-sitter-c/src/parser.c

sat: *.c color_schemes/*.c tree-sitter/lib/src/lib.c $(PARSERS) | formatter.h
	$(CC) -o $@ $(C_FLAGS) $^

.PHONY: test
test: sat main.c
	./sat main.c

