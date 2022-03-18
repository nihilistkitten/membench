CXX := gcc
WARN := -Wall -Werror -Wextra -pedantic 
OPT := -O3
CFLAGS := $(OPT) $(WARN)

HEADERS := types.h
OBJECTS := bench.o
DEPS := $(HEADERS) $(OBJECTS)

all: main

bench.png: data.csv pyproject.toml main.py
	poetry run python main.py

data.csv: main
	./$^ > $@

main: main.c $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CXX) -c $< $(CFLAGS)

clean:
	-rm -f *.o
	-rm -f main
	-rm -f data.csv
	-rm -f bench.png

.PHONY: all clean
