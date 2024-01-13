.PHONY: all
all: test

sat: main.c
	cc -o $@ $^

.PHONY: test
test: sat main.c
	@  cat main.c > cat.out 2> cat.err
	@./sat main.c > sat.out 2> sat.err
	diff cat.out sat.out
	diff cat.err sat.err
	
	@rm cat.out sat.out cat.err sat.err
