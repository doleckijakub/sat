.PHONY: all
all: test

CC = cc

C_FLAGS += -Wswitch
C_FLAGS += -I tree-sitter/lib/src
C_FLAGS += -I tree-sitter/lib/include
C_FLAGS += -I src

PARSERS += parsers/tree-sitter-c/src/parser.c

SRC_FILES += src/*.c
SRC_FILES += color_schemes/*.c
SRC_FILES += tree-sitter/lib/src/lib.c
SRC_FILES += $(PARSERS)

sat: $(SRC_FILES) | src/*.h
	$(CC) -o $@ $(C_FLAGS) $^

.PHONY: test
test: sat src/main.c
	./sat src/main.c

