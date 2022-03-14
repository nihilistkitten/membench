CXX := gcc
WARN := -Wall -Werror -Wextra -pedantic
OPT := -O3
CFLAGS :=  $(OPT) $(WARN)

HEADERS := types.h
DEPS := $(HEADERS)

all: main

main: main.c $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

test: test.o
	./test.o

%.o: %.c $(DEPS)
	$(CXX) -o $@ $< $(CFLAGS)

clean:
	-rm -f main
	-rm -f *.o

.PHONY: all clean test
