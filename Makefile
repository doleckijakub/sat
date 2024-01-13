.PHONY: all
all: test

sat: main.c formatter.c | formatter.h
	cc -o $@ $^

.PHONY: test
test: sat main.c
	./sat main.c

