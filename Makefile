.PHONY: all
all: test

sat: main.c
	cc -o $@ $^

.PHONY: test
test: sat main.c
	./sat main.c
